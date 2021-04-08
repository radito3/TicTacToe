#include "ConsoleWriter.h"
#include "GameSession.h"

int main() {
    //these two statements will be called by the server
    GameSession session(new ConsoleWriter,
                        Player("1", &DisplayWriter::write_circle, &DisplayWriter::write_circle_placeholder),
                        Player("2", &DisplayWriter::write_cross, &DisplayWriter::write_cross_placeholder));
    session.play();

    //this is console-game-specific
    printf(AsciiEscapeCodes::MoveToPos, 15, 15);
    return 0;
}
