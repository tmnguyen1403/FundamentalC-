class Solution {
public:
    string reverseWords(string s) {
        int word_length = 0;
        int word_count = 0;
        int reserve_length = 0;
        auto s_begin = s.begin();
        char sep = ' ';
        while (s_begin != s.end()) {
            if (*s_begin != sep) {
                ++word_length;
            }
            else {
                if (word_length > 0) {
                    word_count += 1;
                    reserve_length += word_length;
                    word_length = 0;
                }
            }
            std::advance(s_begin,1);
        }
        if (word_length > 0) {
            word_count += 1;
            reserve_length += word_length;
            word_length = 0;
        }
        //Reserve size for the result
        reserve_length += word_count - 1;
        std::string result;
        result.resize(reserve_length);
        auto result_end = result.end();

        //start reversing process
        s_begin = s.begin();
        while (s_begin != s.end()) {
            if (*s_begin != sep) {
                ++word_length;
            }
            else {
                if (word_length > 0) {
                    std::advance(result_end, -word_length);
                    //copy the current word to the next end word of result string
                    std::copy(s_begin - word_length, s_begin, result_end);
                    --word_count;
                    if (word_count > 0) {
                        //Add separator (space)
                        --result_end;
                        *result_end = sep;
                    }
                    word_length = 0;
                }
            }
            std::advance(s_begin,1);
        }
        if (word_count > 0) {
            std::advance(result_end, -word_length);
            //copy the current word to the next end word of result string
            std::copy(s_begin - word_length, s_begin, result_end);
            --word_count;
        }
        return result;
    }
};