#ifndef SYMBOL_H
#define SYMBOL_H

enum class Bandsymbol{
    blank,
    zero,
    one,
    hashtag,
    dollarsign
};

static const char* BandsymbolStrings[] = {"blank","zero","one","hashtag","dollarsign"};

const char* getBandsymbolStringsValue(Bandsymbol symbol);

#endif //SYMBOL_H