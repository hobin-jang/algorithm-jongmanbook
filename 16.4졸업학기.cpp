#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>

using namespace std;

int C, N, K, M, L; 
// C: test case, N: 전체 과목 수, K: 들어야할 과목 수
// M: 남은 학기 수, L: 한 학기 최대 수강 과목 수
int pre[12]; // i번째 과목의 선수과목의 집합
int classes[10]; // i번째 학기 개설 과목 집합
int dp[10][1 << 12]; 
// dp[i][j] : i번째 학기동안 j만큼 들었을 때 가능한 최소 학기 수

// 졸업 불가능
int INF = 987654321;

string line = "\n================================\n";

int bitcount(int n) // n의 이진수 값중 1의 개수 세기
{
	if (n == 0)
		return 0;
	return n % 2 + bitcount(n / 2);
}

// semester : 이번 학기 수, taken : 들은 과목 (집합으로 생각)
int graduate(int semester, int taken)
{ 
	// 기저 사례 : 들은 과목 수가 K 이상 : return
	if (bitcount(taken) >= K)
		return 0;
	// 기저 사례 : 학기 수 M 이상 : return
	if (semester == M)
		return INF;

	// result : semester 학기에 taken만큼 과목을 들었을 때 졸업까지 남은 최소 학기
	int& result = dp[semester][taken];
	if (result != -1)
		return result;
	result = INF;
	// canTake : semester 학기에 듣지 않은 과목 (~taken)
	int canTake = (classes[semester] & ~taken);

	// 선수 과목 듣지 않은 것 걸러냄
	for (int i = 0; i < N; i++) {
		if ((canTake & (1 << i)) && ((taken & pre[i]) != pre[i]))
			canTake &= ~(1 << i);
	}

	// 선수 과목 들은 것 (집합) 모두 탐색, 한 학기 최대 L개 수업
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		if (bitcount(take) > L)
			continue;
		result = min(result, graduate(semester + 1, taken | take) + 1);
	}

	// 아무것도 듣지 않을 경우
	result = min(result, graduate(semester + 1, taken));
	return result;
}

int main()
{
	cout << "테스트 케이스 : ";
	cin >> C;
	cout << line;
	while (C--) {
		// 입력
		cout << "전체 과목 수, 들어야 할 과목 수, 남은 학기 수, 한 학기 최대 수강 과목 수 : ";
		cin >> N >> K >> M >> L;
		cout << line;

		// 초기화
		memset(dp, -1, sizeof(dp));
		memset(pre, 0, sizeof(pre));
		memset(classes, 0, sizeof(classes));

		// 선수과목 입력
		cout << "선수 과목 입력 : ";
		for (int i = 0; i < N; i++) {
			int idx;
			cin >> idx;
			for (int j = 0; j < idx; j++) {
				int num;
				cin >> num;
				pre[i] += pow(2, num);
			}
		}
		cout << line;

		// 개설 과목 입력
		cout << "개설 과목 입력 : ";
		for (int i = 0; i < M; i++) {
			int idx;
			cin >> idx;
			for (int j = 0; j < idx; j++) {
				int num;
				cin >> num;
				classes[i] += pow(2, num);
			}
		}
		cout << line;

		cout << "졸업까지 최소 학기 : ";
		int answer = graduate(0, 0);
		if (answer == INF)
			cout << "IMPOSSIBLE" << '\n';
		else
			cout << answer << '\n';
		cout << line;
	}
}