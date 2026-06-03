class Solution {
public:
    struct RideHelper {
        vector<int> start;
        vector<long long> prefMinDur;
        vector<long long> suffMinFinish;

        RideHelper(vector<int>& s, vector<int>& d) {
            int n = s.size();

            vector<pair<int,int>> rides;
            for (int i = 0; i < n; i++) {
                rides.push_back({s[i], d[i]});
            }

            sort(rides.begin(), rides.end());

            start.resize(n);
            prefMinDur.resize(n);
            suffMinFinish.resize(n);

            for (int i = 0; i < n; i++) {
                start[i] = rides[i].first;
            }

            prefMinDur[0] = rides[0].second;
            for (int i = 1; i < n; i++) {
                prefMinDur[i] = min(prefMinDur[i - 1],
                                    (long long)rides[i].second);
            }

            suffMinFinish[n - 1] =
                (long long)rides[n - 1].first + rides[n - 1].second;

            for (int i = n - 2; i >= 0; i--) {
                suffMinFinish[i] = min(
                    suffMinFinish[i + 1],
                    (long long)rides[i].first + rides[i].second
                );
            }
        }

        long long query(long long finishTime) {
            long long ans = LLONG_MAX;
            int n = start.size();

            int idx = upper_bound(start.begin(), start.end(),
                                  finishTime) - start.begin() - 1;

            if (idx >= 0) {
                ans = min(ans, finishTime + prefMinDur[idx]);
            }

            int pos = upper_bound(start.begin(), start.end(),
                                  finishTime) - start.begin();

            if (pos < n) {
                ans = min(ans, suffMinFinish[pos]);
            }

            return ans;
        }
    };

    long long earliestFinishTime(vector<int>& landStartTime,
                                 vector<int>& landDuration,
                                 vector<int>& waterStartTime,
                                 vector<int>& waterDuration) {

        RideHelper water(waterStartTime, waterDuration);
        RideHelper land(landStartTime, landDuration);

        long long ans = LLONG_MAX;

        // Land -> Water
        for (int i = 0; i < landStartTime.size(); i++) {
            long long finishLand =
                (long long)landStartTime[i] + landDuration[i];

            ans = min(ans, water.query(finishLand));
        }

        // Water -> Land
        for (int j = 0; j < waterStartTime.size(); j++) {
            long long finishWater =
                (long long)waterStartTime[j] + waterDuration[j];

            ans = min(ans, land.query(finishWater));
        }

        return ans;
    }
};
