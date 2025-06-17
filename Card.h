#pragma once
#include <iostream>
#include <string>
#define RANK_COUNT 13
#define SUITE_COUNT 4

// Define enums for Suit and Rank
enum class Suite 
{
    Spades,
    Hearts,
    Diamonds,
    Clubs
};

enum class Rank 
{
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

struct Card
{
    Suite suite;
    Rank rank;
} typedef Card;

/// <summary>
/// display a card
/// </summary>
/// <param name="card">the card to display</param>
void displayCard(const Card& card);