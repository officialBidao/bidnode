void AES::shiftrow(std::vector <std::vector <uint8_t> > & data){
    std::vector <std::vector <uint8_t> > temp;
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> row;
        for(uint8_t y = 0; y < 4; y++){
            row.push_back(data[y][x]);
        }
        temp.push_back(row);
    }
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> t = temp[x];
        uint8_t count = 0;
        for(uint8_t y = x; y < 4; y++){
            temp[x][count] = t[y];
            count++;
        }
        for(uint8_t y = 0; y < x; y++){
            temp[x][count] = t[y];
            count++;
        }
    }
    for(uint8_t x = 0; x < 4; x++)
        for(uint8_t y = 0; y < 4; y++)
            data[x][y] = temp[y][x];
}
void AES::invshiftrow(std::vector <std::vector <uint8_t> > & data){
    std::vector <std::vector <uint8_t> > temp;
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> row;
        for(uint8_t y = 0; y < 4; y++){
            row.push_back(data[y][x]);
        }
        temp.push_back(row);
    }
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> t = temp[x];
        uint8_t count = 0;
        for(uint8_t y = (4 - x) & 3; y < 4; y++){
            temp[x][count] = t[y];
            count++;
        }
        for(uint8_t y = 0; y < (4 - x) & 3; y++){
            temp[x][count] = t[y];
            count++;
        }
    }
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] = temp[y][x];
        }
    }
}
//uint8_t AES::GF(uint8_t a, uint8_t b){
//    //rijndael Finite Field multiplication
//    uint8_t prim = 0x11b;
//    std::string A = makebin(a, 8);
//    std::string B = makebin(b, 8);
//    uint8_t c = 0;
//    for (uint8_t i = 7; i >= 0; i--){
//        std::string temp = "";
//        for (uint8_t j = 7; i >= 0; i--){
//            temp = str(atoi(a[j]) * atoi(b[i])) + temp;
//        }
//        c ^= int(temp + "0" * (7-i), 2);
//    }
//    for (uint8_t i = 15; i > 7; i--){
//        if (makebin(c, i)[0] == "1"){
//            c ^= prim << (i-9);
//        }
//    }
//    return c
//}
uint8_t AES::GF(uint8_t a, uint8_t b){
//    Rijndael Finite Field multiplication
//    Fast but Vulnerable to Timing Attacks
//    From Wikipedia
    uint8_t prim = 0x1b;
    uint8_t p = 0, i = 0;
    while ((i < 8) && (a != 0) and (b != 0)){
        if (b & 1){
            p ^= a;
        }
        uint8_t hi = a & 0x80;
        a = (a << 1) & 255;
        if ((char) makebin(hi)[0] == '1'){
            a ^= prim;
        }
        b >>= 1;
        i += 1;
    }
    return p;
}
void AES::mixcolumns(std::vector <std::vector <uint8_t> > & data){
    std::vector <std::vector <uint8_t> > temp;
    for(uint8_t i = 0; i < 4; i++){
        std::vector <uint8_t> a;
        a.push_back(GF(2, data[i][0]) ^ GF(3, data[i][1]) ^ data[i][2] ^ data[i][3]);
        a.push_back(GF(2, data[i][1]) ^ GF(3, data[i][2]) ^ data[i][3] ^ data[i][0]);
        a.push_back(GF(2, data[i][2]) ^ GF(3, data[i][3]) ^ data[i][0] ^ data[i][1]);
        a.push_back(GF(2, data[i][3]) ^ GF(3, data[i][0]) ^ data[i][1] ^ data[i][2]);
        temp.push_back(a);
    }
    data = temp;
}
void AES::invmixcolumns(std::vector <std::vector <uint8_t> > & data){
    std::vector <std::vector <uint8_t> > temp;
    for(uint8_t i = 0; i < 4; i++){
        std::vector <uint8_t> a;
        a.push_back(GF(14, data[i][0]) ^ GF(9, data[i][3]) ^ GF(13, data[i][2]) ^ GF(11, data[i][1]));
        a.push_back(GF(14, data[i][1]) ^ GF(9, data[i][0]) ^ GF(13, data[i][3]) ^ GF(11, data[i][2]));
        a.push_back(GF(14, data[i][2]) ^ GF(9, data[i][1]) ^ GF(13, data[i][0]) ^ GF(11, data[i][3]));
        a.push_back(GF(14, data[i][3]) ^ GF(9, data[i][2]) ^ GF(13, data[i][1]) ^ GF(11, data[i][0]));
        temp.push_back(a);
    }
    data = temp;
}
std::string AES::OUT(std::vector <std::vector <uint8_t> > & data){
    std::string out = "";
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            out += data[x][y];
        }
    }
    return out;
}
AES::AES(){
    keyset = false;
}
AES::AES(const std::string & KEY){
    keyset = false;
    setkey(KEY);
}
void setkey(std::string KEY){
    if (keyset){
        error(2);
    }
    for(uint8_t x = 0; x < 256; x++){
        AES_Subbytes[x] = s[x];
        AES_Inv_Subbytes[x] = is[x];
    }
    if (KEY.size() > 32){
        KEY = KEY.substr(0, 32);
    }
    while ((KEY.size() != 16) & (KEY.size() != 24) & (KEY.size() != 32)){// not part of standard
        KEY += zero;
    }
    unsigned uint8_t n = KEY.size();
    rounds = n / 4 + 6;
    columns = rounds - 6;
    b = (rounds + 1) << 4;
    n >>= 2;
    std::vector <std::vector <uint8_t> > key;
    for(uint8_t i = 0; i < columns; i++){
        std::vector <uint8_t> temp;
        for(uint8_t j = 0; j < 4; j++){
            temp.push_back(KEY[4 * i + j]);
        }
        key.push_back(temp);
    }
    uint8_t i = 1;
    while ((key.size() << 2) < b){
        std::vector <uint8_t> t;
        t.push_back(key[key.size() - 1][1]);
        t.push_back(key[key.size() - 1][2]);
        t.push_back(key[key.size() - 1][3]);
        t.push_back(key[key.size() - 1][0]);
        for(uint8_t j = 0; j < 4; j++){
            t[j] = AES_Subbytes[t[j]] ^ key[key.size() - n][j];
        }
        t[0] ^= (1 << (i++ - 1)) % 229;
        key.push_back(t);
        for(uint8_t j = 0; j < 3; j++){
            std::vector <uint8_t> next;
            for(uint8_t k = 0; k < 4; k++){
                next.push_back(key[key.size() - 1][k]^ key[key.size() - n][k]);
            }
            key.push_back(next);
        }
        if (n == 8){
            t = key[key.size() - 1];
            for(uint8_t j = 0; j < 4; j++){
                t[j] = AES_Subbytes[t[j]] ^ key[key.size() - n][j];
            }
            key.push_back(t);
        }
        for(uint8_t j = 0; j < 0 * (n == 4) + 2 * (n == 6) + 3 * (n == 8); j++){
            t.clear();
            for(uint8_t k = 0; k < 4; k++){
                t.push_back(key[key.size() - 1][k] ^ key[key.size() - n][k]);
            }
            key.push_back(t);
        }
    }
    for(uint8_t j = 0; j < (b >> 4); j++){
        std::vector <std::vector <uint8_t> > temp;
        for(uint8_t k = 0; k < 4; k++){
            temp.push_back(key[4 * j + k]);
        }
        keys.push_back(temp);
    }
    keyset = true;
}
std::string AES::encrypt(const std::string & DATA){
    if (!keyset)
        error(1);
    std::vector <std::vector <uint8_t> > data;
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> temp;
        for(uint8_t y = 0; y < 4; y++){
            temp.push_back(DATA[x << 2 + y]);
        }
        data.push_back(temp);
    }
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] ^= keys[0][x][y];
        }
    }
    for(uint8_t r = 1; r < rounds; r++){
        for(uint8_t x = 0; x < 4; x++){
            for(uint8_t y = 0; y < 4; y++){
                data[x][y] = AES_Subbytes[data[x][y]];
            }
        }
        shiftrow(data);
        mixcolumns(data);
        for(uint8_t x = 0; x < 4; x++)
            for(uint8_t y = 0; y < 4; y++)
                data[x][y] ^= keys[r][x][y];
    }
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] = AES_Subbytes[data[x][y]];
        }
    }
    shiftrow(data);
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] ^= keys[rounds][x][y];
        }
    }
    return OUT(data);
}
std::string AES::decrypt(const std::string & DATA){
    if (!keyset){
        error(1);
    }
    std::reverse(keys.begin(), keys.end());
    std::vector <std::vector <uint8_t> > data;
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> temp;
        for(uint8_t y = 0; y < 4; y++){
            temp.push_back(DATA[x << 2 + y]);
        }
        data.push_back(temp);
    }
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] ^= keys[0][x][y];
        }
    }
    for(uint8_t r = 1; r < rounds; r++){
        invshiftrow(data);
        for(uint8_t x = 0; x < 4; x++){
            for(uint8_t y = 0; y < 4; y++){
                data[x][y] = AES_Inv_Subbytes[data[x][y]];
            }
        }
        for(uint8_t x = 0; x < 4; x++){
            for(uint8_t y = 0; y < 4; y++){
                data[x][y] ^= keys[r][x][y];
            }
        }
        invmixcolumns(data);
    }
    invshiftrow(data);
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] = AES_Inv_Subbytes[data[x][y]];
        }
    }
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] ^= keys[rounds][x][y];
        }
    }
    std::reverse(keys.begin(), keys.end());
    return OUT(data);
}
unsigned int AES::blocksize(){
    return 128;
}
