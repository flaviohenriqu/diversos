from collections import namedtuple

Card = namedtuple('Card', 'rank suit')

# class Card:
#     def __init__(self, rank, suit):
#         self.suit = suit
#         self.rank = rank
#
#     def __eq__(self, other):
#         return self.suit == other.suit and self.rank == other.rank


class Deck:
    SUITS = ["spades", "diamonds", "clubs", "hearts"]
    RANKS = '2 3 4 5 6 7 8 9 10 J Q K A'.split()

    def __init__(self):
        self.cards = [Card(r, s) for s in self.SUITS for r in self.RANKS]

    def __getitem__(self, item):
        return self.cards[item]

    def __setitem__(self, key, value):
        self.cards[key] = value

    def __len__(self):
        return len(self.cards)


def main():
    deck = Deck()
    assert deck
    assert len(deck) == 52
    assert Card(rank='2', suit='spades') == Card(rank='2', suit='spades')
    assert deck[0] == Card(rank='2', suit='spades')
    assert deck[:2] == [Card('2', 'spades'), Card('3', 'spades')]
    assert deck[12::13] == [Card('A', 'spades'), Card('A', 'diamonds'),
                            Card('A', 'clubs'), Card('A', 'hearts')]
    assert Card('Q', 'hearts') in Deck()
    #
    deck[0] = None; assert deck[0] is None
    deck[:2] = [None, None]; assert deck[:2] == [None, None]


if __name__ == '__main__':
    main()