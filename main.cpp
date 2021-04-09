#include "ConsoleWriter.h"
#include "ConsoleReader.h"
#include "GameSession.h"

int main() {
    //these two statements will be called by the server
    GameSession session(Player("1", &DisplayWriter::write_circle, &DisplayWriter::write_circle_placeholder),
                        Player("2", &DisplayWriter::write_cross, &DisplayWriter::write_cross_placeholder),
                        new ConsoleWriter, new ConsoleReader);
    session.play();

    //this is console-game-specific
    printf(AsciiEscapeCodes::MoveToPos, 15, 15);
    return 0;
}
