class Solution {
public:
    int numberOfSpecialChars(string word) {
        vector<int> lastLower(26, -1);
        vector<int> firstUpper(26, INT_MAX);

        // Store last lowercase index and first uppercase index
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];

            if (islower(ch)) {
                lastLower[ch - 'a'] = i;
            } else {
                firstUpper[ch - 'A'] = min(firstUpper[ch - 'A'], i);
            }
        }

        int count = 0;

        // Check special characters
        for (int i = 0; i < 26; i++) {
            if (lastLower[i] != -1 &&
                firstUpper[i] != INT_MAX &&
                lastLower[i] < firstUpper[i]) {
                count++;
            }
        }

        return count;
    }
};
