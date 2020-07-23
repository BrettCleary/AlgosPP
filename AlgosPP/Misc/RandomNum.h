
namespace algospp {
namespace {
    int randomNumber = 0;
    int counter = 0;
    int seed = 0;
}//unnamed namespace

int RandNum() {
    if (counter > RAND_MAX) {
        ++seed;
        srand(seed);
        counter = 0;
    }

    int bitToFlip = rand() * (sizeof(int) * 8 - 1) / RAND_MAX;
    if ((1 << bitToFlip) & randomNumber) {
        //clear bit
        randomNumber &= ~(1 << bitToFlip);
    }
    else {
        //set bit
        randomNumber |= 1 << bitToFlip;
    }

    ++counter;
    return randomNumber;
}
}//algospp