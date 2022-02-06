#include <catch2/catch.hpp>
#include <model/board.h>

TEST_CASE("Test linears moves from board", "[board][move][linear]")
{
    Board board;
    Player* currentPlayer = new Player(Color::BLACK);

    SECTION("A1B1 valid linear move") {
        board.move({8, 0}, {7, 1}, currentPlayer);
        REQUIRE(board.hexagonColor({8, 0}) == Color::NONE);
        REQUIRE(board.hexagonColor({7, 1}) == Color::BLACK);
        REQUIRE(board.hexagonColor({6, 2}) == Color::BLACK);
        REQUIRE(board.hexagonColor({5, 3}) == Color::BLACK);
    }

    SECTION("B2C1 invalid linear move") {
        REQUIRE_FALSE(board.move({7, 1}, {6, 0}, currentPlayer));
    }

    SECTION("C3B2 out of bounds invalid linear move") {
        REQUIRE_FALSE(board.move({6, 2}, {7, 1}, currentPlayer));
    }

    SECTION("I5H5 invalid linear move, wrong player") {
        REQUIRE_FALSE(board.move({0, 4}, {1, 4}, currentPlayer));
    }

    SECTION("I5H5 invalid linear move, null hexagon") {
        REQUIRE_FALSE(board.move({0, 0}, {0, 1}, currentPlayer));
    }

    SECTION("A1B1 invalid linear move. Too much marbles") {
        board.changeColor({5, 3}, Color::BLACK);
        REQUIRE_FALSE(board.move({8, 0}, {7, 1}, currentPlayer));
    }

    SECTION("A1B1 invalid linear move. Opponent marbles blocking") {
        board.changeColor({5, 3}, Color::WHITE);
        board.changeColor({4, 4}, Color::WHITE);
        board.changeColor({3, 5}, Color::WHITE);
        REQUIRE_FALSE(board.move({8, 0}, {7, 1}, currentPlayer));
    }

    SECTION("A1B1 valid linear move. Push opponent marbles") {
        board.changeColor({5, 3}, Color::WHITE);
        board.changeColor({4, 4}, Color::WHITE);
        board.move({8, 0}, {7, 1}, currentPlayer);
        REQUIRE(board.hexagonColor({8, 0}) == Color::NONE);
        REQUIRE(board.hexagonColor({7, 1}) == Color::BLACK);
        REQUIRE(board.hexagonColor({6, 2}) == Color::BLACK);
        REQUIRE(board.hexagonColor({5, 3}) == Color::BLACK);
        REQUIRE(board.hexagonColor({4, 4}) == Color::WHITE);
        REQUIRE(board.hexagonColor({3, 5}) == Color::WHITE);
    }

    SECTION("F7G8 valid linear move. Opponent marble ejected") {
        board.changeColor({3, 6}, Color::BLACK);
        board.changeColor({2, 7}, Color::BLACK);
        board.move({3, 6}, {2, 7}, currentPlayer);
        REQUIRE(board.hexagonColor({3, 6}) == Color::NONE);
        REQUIRE(board.hexagonColor({2, 7}) == Color::BLACK);
        REQUIRE(currentPlayer->ejectedOpponentMarbles() == 1);
    }

    SECTION("I5H5 valid linear move with other player") {
        currentPlayer->color(Color::WHITE);
        board.move({0, 4}, {1, 4}, currentPlayer);
        REQUIRE(board.hexagonColor({0, 4}) == Color::NONE);
        REQUIRE(board.hexagonColor({1, 4}) == Color::WHITE);
        REQUIRE(board.hexagonColor({2, 4}) == Color::WHITE);
        REQUIRE(board.hexagonColor({3, 4}) == Color::WHITE);
    }

    free(currentPlayer);

}

TEST_CASE("Test lateral moves from board", "[board][move][lateral]")
{
    Board board;
    Player* currentPlayer = new Player(Color::BLACK);

    SECTION("C5C3D5 valid lateral left move") {
        board.move({6, 4}, {6, 2}, {5, 4}, currentPlayer);
        REQUIRE(board.hexagonColor({5, 2}) == Color::BLACK);
        REQUIRE(board.hexagonColor({5, 3}) == Color::BLACK);
        REQUIRE(board.hexagonColor({5, 4}) == Color::BLACK);
        REQUIRE(board.hexagonColor({6, 2}) == Color::NONE);
        REQUIRE(board.hexagonColor({6, 3}) == Color::NONE);
        REQUIRE(board.hexagonColor({6, 4}) == Color::NONE);
    }

    SECTION("C3C5D4 valid lateral right move") {
        board.move({6, 2}, {6, 4}, {5, 3}, currentPlayer);
        REQUIRE(board.hexagonColor({5, 3}) == Color::BLACK);
        REQUIRE(board.hexagonColor({5, 4}) == Color::BLACK);
        REQUIRE(board.hexagonColor({5, 5}) == Color::BLACK);
        REQUIRE(board.hexagonColor({6, 2}) == Color::NONE);
        REQUIRE(board.hexagonColor({6, 3}) == Color::NONE);
        REQUIRE(board.hexagonColor({6, 4}) == Color::NONE);
    }

    SECTION("C5C3D3 invalid lateral move") {
        REQUIRE_FALSE(board.move({6, 4}, {6, 2}, {5, 2}, currentPlayer));
    }

    SECTION("C3C5D2 invalid lateral move 2") {
        REQUIRE_FALSE(board.move({6, 2}, {6, 4}, {5, 1}, currentPlayer));
    }

    SECTION("E7E9F8 invalid lateral move out of bounds") {
        board.changeColor({4, 6}, Color::BLACK);
        board.changeColor({4, 7}, Color::BLACK);
        board.changeColor({4, 8}, Color::BLACK);
        REQUIRE_FALSE(board.move({4, 6}, {4, 8}, {3, 7}, currentPlayer));
    }

    SECTION("G5G7F5 invalid lateral move, wrong player") {
        REQUIRE_FALSE(board.move({2, 4}, {2, 6}, {3, 4}, currentPlayer));
    }

    SECTION("C5C2D5 invalid lateral move. Too much marbles") {
        board.changeColor({6, 1}, Color::BLACK);
        REQUIRE_FALSE(board.move({6, 4}, {6, 1}, {5, 4}, currentPlayer));
    }

    SECTION("C5C3D5 invalid lateral move. Opponent marbles blocking") {
        board.changeColor({5, 3}, Color::WHITE);
        REQUIRE_FALSE(board.move({6, 4}, {6, 2}, {5, 4}, currentPlayer));
    }

    SECTION("G5G7F5 valid lateral move with other player") {
        currentPlayer->color(Color::WHITE);
        board.move({2, 4}, {2, 6}, {3, 4}, currentPlayer);
        REQUIRE(board.hexagonColor({3, 4}) == Color::WHITE);
        REQUIRE(board.hexagonColor({3, 5}) == Color::WHITE);
        REQUIRE(board.hexagonColor({3, 6}) == Color::WHITE);
        REQUIRE(board.hexagonColor({2, 4}) == Color::NONE);
        REQUIRE(board.hexagonColor({2, 5}) == Color::NONE);
        REQUIRE(board.hexagonColor({2, 6}) == Color::NONE);
    }

    free(currentPlayer);
}
