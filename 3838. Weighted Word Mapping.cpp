class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string result;

        for (const string& word : words) {
            int sum = 0;

            for (char ch : word) {
                sum += weights[ch - 'a'];
            }

            int mod = sum % 26;
            result.push_back('z' - mod);
        }

        return result;
    }
};
