#include "HandDeterminator.h"

Hand* HandDeterminator::determineHand(const std::vector<Card>& fullHand)
{
    _fullHand = fullHand;
    // sort the hand in a descending order using a lambda function
    std::sort(_fullHand.begin(), _fullHand.end(), [](Card a, Card b) { return a.rank > b.rank; });

    initHashMaps();  // initiate the hash maps

    // check for the possible hands from best to worse and stop once the best hand is found
    if (checkRoyalStraightFlush() || checkFourOfAKind() || checkFullHouse() ||
        checkFlush() || checkStraight() || checkThreeOfAKind() || checkPairsHighCard())
    { }

    return _hand;
}

bool HandDeterminator::checkRoyalStraightFlush()
{
    // NOTE: we're checking for a straight flush manually and not using checkStraight() and checkFlush() becuase
    // they would give us the best straights and flushs and there might be multiple straights and flushes, and so
    // we have to check manually which straight also constructs a flush
    Card topCard;
    Card prevCard;
    int straightFlushLength = 0;

    for (int i = 0; i < _fullHand.size(); i++)
    {
        if (straightFlushLength == 0)  // beginning of a straight
        {
            // define new top card and
            topCard = _fullHand[i];
            prevCard = topCard;
            straightFlushLength++;
        }
        else if ((int)prevCard.rank == (int)_fullHand[i].rank + 1 &&
                    prevCard.suite == _fullHand[i].suite)  // continuation of the straight flush
        {
            prevCard = _fullHand[i];
            straightFlushLength++;
            if (straightFlushLength == STRAIGHT_LENGTH ||  // check if a straight flush is complete
                (straightFlushLength == STRAIGHT_LENGTH - 1 && _fullHand[i].rank == Rank::Two && _fullHand.front().rank == Rank::Ace &&
                    _fullHand.front().suite == _fullHand[i].suite))  // check for a bicycle straight!
            {
                if (topCard.rank == Rank::Ace)  // royal flush is a straight flush beginning with an ace
                {
                    _hand = new RoyalFlush();
                }
                else  // standard straight flush
                {
                    _hand = new StraightFlush(topCard);
                }
                return true;
            }
        }
        else if (_fullHand[i].rank != prevCard.rank)  // don't break straight in case of a duplicate card
        {
            straightFlushLength = 0;
            i--;  // reduce i to start the new straight flush from the current card
        }
    }
    return false;

}

bool HandDeterminator::checkFourOfAKind()
{
    bool fourOfAKindFound = false;
    int kickerCount = 0;
    std::vector<Card> fourOfAkindCard;

    for (int i = _rankHashMap.size() - 1; i >= 0; i--)
    {
        if (_rankHashMap[i] == 4)   // if a four of a kind is found
        {
            fourOfAkindCard.insert(fourOfAkindCard.begin(), (Card{ Suite::Spades, (Rank)i }));  // suite of the card is irrelevant, insert card at the beginning
            fourOfAKindFound = true;
        }
        else if (kickerCount < FOUR_OF_A_KIND_KICKER_COUNT && _rankHashMap[i] > 0)  // check if card is a kicker
        {
            fourOfAkindCard.push_back(Card{ Suite::Spades, (Rank)i });  // suite of the card is irrelevant
            kickerCount++;
        }
    }
    if (fourOfAKindFound)
    {
        _hand = new FourOfAKind(fourOfAkindCard);
        return true;
    }
    return false;
}

bool HandDeterminator::checkFullHouse()
{
    std::vector<Card> setAndPair;

    if (checkThreeOfAKind())  // check for set
    {
        setAndPair.push_back(dynamic_cast<const ThreeOfAKind&>(*_hand).getSet().front());  // push set card into the setAndPair vector
        
        checkPairsHighCard();  // check for pair or two pair
        if (dynamic_cast<TwoPair*>(_hand) != nullptr)  // check if there is a two pair
        {
            setAndPair.push_back(dynamic_cast<const TwoPair&>(*_hand).getPairs().front());  // push top pair card into the setAndPair vector
            _hand = new FullHouse(setAndPair);
            return true;
        }
        else if (dynamic_cast<Pair*>(_hand) != nullptr)  // check if there is a pair
        {
            setAndPair.push_back(dynamic_cast<const Pair&>(*_hand).getPair().front());  // push pair card into the setAndPair vector
            _hand = new FullHouse(setAndPair);
            return true;
        }
    }

    return false;
}

bool HandDeterminator::checkFlush()
{
    std::vector<Card> flushCards;
    for (int i = 0; i < _suiteHashMap.size(); i++)
    {
        if (_suiteHashMap[i] >= 5)  // flush found
        {
            for (int j = 0; j < _fullHand.size() && flushCards.size() < 5; j++)  // only take the top 5 cards of the same suite for the flush
            {
                if (_fullHand[j].suite == (Suite)i)  // add the 5 top cards of the flush suite
                {
                    flushCards.push_back(_fullHand[j]);
                }
            }
            _hand = new Flush(flushCards);
            return true;
        }
    }
    return false;
}

bool HandDeterminator::checkStraight()
{
    Card topCard;
    Card prevCard;
    int straightLength = 0;

    for (int i = 0; i < _fullHand.size(); i++)
    {
        if (straightLength == 0)  // beginning of a straight
        {
            // set new top card
            topCard = _fullHand[i];
            prevCard = topCard;
            straightLength++;
        }
        else if ((int)prevCard.rank == (int)_fullHand[i].rank + 1)  // continuation of the straight
        {
            prevCard = _fullHand[i];
            straightLength++;
            if (straightLength == STRAIGHT_LENGTH ||  // check if a straight is complete
                (straightLength == STRAIGHT_LENGTH - 1 && _fullHand[i].rank == Rank::Two && _fullHand.front().rank == Rank::Ace))  // check for a bicycle straight!
            {
                _hand = new Straight(topCard);
                return true;
            }
        }
        else if (_fullHand[i].rank != prevCard.rank)  // don't break straight in case of a duplicate card
        {
            straightLength = 0;
            i--;  // reduce i to start the new straight from the current card
        }
    }
    return false;
}

bool HandDeterminator::checkThreeOfAKind()
{
    std::vector<Card> set;
    bool setFound = false;
    int kickerCount = 0;

    for (int i = _rankHashMap.size() - 1; i >= 0; i--)
    {
        if (!setFound && _rankHashMap[i] == 3)   // if a set is found
        {
            // insert set at the beginning of the set vector
            set.insert(set.begin(), Card{ Suite::Spades, (Rank)i });  // suite of the card is irrelevant
            setFound = true;
        }
        else if (kickerCount < THREE_OF_A_KIND_KICKER_COUNT && _rankHashMap[i] > 0)
        {
            set.push_back(Card{ Suite::Spades, (Rank)i });  // suite of the card is irrelevant
            kickerCount++;
        }
    }

    if (setFound)
    {
        _hand = new ThreeOfAKind(set);
        return true;
    }
    return false;
}

bool HandDeterminator::checkPairsHighCard()
{
    std::vector<Card> pairs;
    int pairCount = 0;
    int kickerCount = 0;

    for (int i = _rankHashMap.size() - 1; i >= 0; i--)
    {
        if (pairCount < 2 && _rankHashMap[i] == 2)   // if a pair is found
        {
            // insert first pair card at the beginning of the pairs vector
            if (pairCount == 0)
            {
                pairs.insert(pairs.begin(), Card{ Suite::Spades, (Rank)i });  // suite of the card is irrelevant
            }
            else  // second pair is found, insert it after the first pair
            {
                pairs.insert(pairs.begin() + 1, Card{ Suite::Spades, (Rank)i });  // suite of the card is irrelevant
            }
            pairCount++;
        }
        else if (kickerCount < MAX_KICKER_COUNT && _rankHashMap[i] > 0)  // if the card is not a pair or irrelevant pair then add it as a kicker
        {
            pairs.push_back(Card{ Suite::Spades, (Rank)i });  // suite of the card is irrelevant
            kickerCount++;
        }
    }

    if (pairCount == 2)
    {
        _hand = new TwoPair(std::vector<Card>(pairs.begin(), pairs.begin() + 3));  // create two pair with two pair cards and one kicker
    }
    else if (pairCount == 1)
    {
        _hand = new Pair(std::vector<Card>(pairs.begin(), pairs.begin() + 4));  // create pair with pair card and 3 kickers
    }
    else
    {
        _hand = new HighCard(std::vector<Card>(pairs.begin(), pairs.begin() + 5));  // create high card with 5 kicker cards
    }
    return true;
}

void HandDeterminator::initHashMaps()
{
    for (int i = 0; i < RANK_COUNT; i++)   // initiate the empty hash maps
    {
        _rankHashMap.push_back(0);
    }

    for (int i = 0; i < SUITE_COUNT; i++)
    {
        _suiteHashMap.push_back(0);
    }

    for (int i = 0; i < _fullHand.size(); i++)  // update the hash maps according to the hand
    {
        _rankHashMap[(int)_fullHand[i].rank]++;
        _suiteHashMap[(int)_fullHand[i].suite]++;
    }
}
