#pragma once

#include <string_view>
#include <memory>
#include <cstdio>
#include <cassert>
#include <unordered_map>

namespace CCC
{
  enum class TokenKind
  {
    Id,

    If, Else, While, Do, For, Return,
    Auto, Static, Extern, Typedef, Register,
    Void, Bool, Char, Short, Int, Long,
    Float, Double, Signed, UnSigned,
    Const, Restrict, Volatile,
    SizeOf, Struct, Union, Enum, Break, Continue,
    Goto, Switch, Case, Default,

    Plus, Minus, Star, Slash, LParen,
    RParen, LBracket, RBracket, LBrace, RBrace,
    Semicolon, Assign, Comma, Amp, Equal,
    PipeEqual, Greater, GreaterEqual, Lesser,
    LesserEqual, Period, Arrow, Ellipsis, LongLong, Colon,

    Num,
    Eof
  };

  struct SourceLocation
  {
    const char *FilePath;
    std::string_view Code;
    int LineHead;
    int Line;
    int Col;
  };

  class Token
  {
  public:
    TokenKind Kind;
    int Value;
    SourceLocation Location;
    std::string_view Content;
  };

  class PeekPoint
  {
  public:
    char CurChar;
    int Cursor;
    int Line;
    int LineHead;
    std::shared_ptr<Token> CurrentToken;
  };

  class Lexer
  {
  private:
    char CurChar{' '};
    int Cursor{0};
    int Line{0};
    int LineHead{0};
    PeekPoint PeekPt;
    std::string_view SourceCode;
    char *CodeBuf{nullptr};
    const char *CurrentFilePath{nullptr};
  public:
    std::shared_ptr<Token> CurrentToken;
  public:
    Lexer(const char *filePath){
      CurrentFilePath = filePath;
      FILE *fp = fopen(filePath, "r");
      if (fp) {
        fseek(fp, 0, SEEK_END);
        long fileSize = ftell(fp);
        CodeBuf = (char *)malloc(fileSize + 1);
        CodeBuf[fileSize] = '\0';
        fseek(fp, 0, SEEK_SET);
        fread(CodeBuf, fileSize, 1, fp);
        fclose(fp);
      }else {
        printf("%s open failed\n", filePath);
        assert(0);
      }
      SourceCode = CodeBuf;
    }
    void GetNextToken();
    void GetNextChar();
    void ExpectToken(TokenKind kind);
    void SkipToken(TokenKind kind);
    bool Match(TokenKind kind);

    void BeginPeekToken();
    void EndPeekToken();

  private:
    bool IsLetter();
    bool IsDigit();
    bool IsLetterOrDigit();

    char PeekChar(int distance);

    void SkipWhiteSpace();
    void SkipComment();

    SourceLocation GetLocation();

    const char *GetTokenSimpleSpelling(TokenKind kind);
  };
}

#endif // CCC_LEXER_H
