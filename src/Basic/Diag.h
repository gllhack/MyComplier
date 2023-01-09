#pragma once
#include "Lexer.h"
#include <string_view>

namespace CCC {

  #define LexDiag(loc, fmt, ...)       DiagLoc(DiagPhase::LexPhase, loc, fmt, ##__VA_ARGS__);
  #define ParseDiag(loc, fmt, ...)     DiagLoc(DiagPhase::ParsePhase, loc, fmt, ##__VA_ARGS__);
  #define SemaDiag(loc, fmt, ...)      DiagLoc(DiagPhase::SemaPhase, loc, fmt, ##__VA_ARGS__);
  #define GenDiag(loc, fmt, ...)       DiagLoc(DiagPhase::CodeGenPhase, loc, fmt, ##__VA_ARGS__);

  enum class DiagPhase {
    LexPhase,
    ParsePhase,
    SemaPhase,
    CodeGenPhase
  };

  void DiagLoc(DiagPhase diagPhase, SourceLocation loc, const char*fmt, ...);


}

#endif //CCC_SRC_DIAG_H
