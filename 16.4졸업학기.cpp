#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>

using namespace std;

int C, N, K, M, L; 
// C: test case, N: ��ü ���� ��, K: ������ ���� ��
// M: ���� �б� ��, L: �� �б� �ִ� ���� ���� ��
int pre[12]; // i��° ������ ���������� ����
int classes[10]; // i��° �б� ���� ���� ����
int dp[10][1 << 12]; 
// dp[i][j] : i��° �б⵿�� j��ŭ ����� �� ������ �ּ� �б� ��

// ���� �Ұ���
int INF = 987654321;

string line = "\n================================\n";

int bitcount(int n) // n�� ������ ���� 1�� ���� ����
{
	if (n == 0)
		return 0;
	return n % 2 + bitcount(n / 2);
}

// semester : �̹� �б� ��, taken : ���� ���� (�������� ����)
int graduate(int semester, int taken)
{ 
	// ���� ��� : ���� ���� ���� K �̻� : return
	if (bitcount(taken) >= K)
		return 0;
	// ���� ��� : �б� �� M �̻� : return
	if (semester == M)
		return INF;

	// result : semester �б⿡ taken��ŭ ������ ����� �� �������� ���� �ּ� �б�
	int& result = dp[semester][taken];
	if (result != -1)
		return result;
	result = INF;
	// canTake : semester �б⿡ ���� ���� ���� (~taken)
	int canTake = (classes[semester] & ~taken);

	// ���� ���� ���� ���� �� �ɷ���
	for (int i = 0; i < N; i++) {
		if ((canTake & (1 << i)) && ((taken & pre[i]) != pre[i]))
			canTake &= ~(1 << i);
	}

	// ���� ���� ���� �� (����) ��� Ž��, �� �б� �ִ� L�� ����
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		if (bitcount(take) > L)
			continue;
		result = min(result, graduate(semester + 1, taken | take) + 1);
	}

	// �ƹ��͵� ���� ���� ���
	result = min(result, graduate(semester + 1, taken));
	return result;
}

int main()
{
	cout << "�׽�Ʈ ���̽� : ";
	cin >> C;
	cout << line;
	while (C--) {
		// �Է�
		cout << "��ü ���� ��, ���� �� ���� ��, ���� �б� ��, �� �б� �ִ� ���� ���� �� : ";
		cin >> N >> K >> M >> L;
		cout << line;

		// �ʱ�ȭ
		memset(dp, -1, sizeof(dp));
		memset(pre, 0, sizeof(pre));
		memset(classes, 0, sizeof(classes));

		// �������� �Է�
		cout << "���� ���� �Է� : ";
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

		// ���� ���� �Է�
		cout << "���� ���� �Է� : ";
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

		cout << "�������� �ּ� �б� : ";
		int answer = graduate(0, 0);
		if (answer == INF)
			cout << "IMPOSSIBLE" << '\n';
		else
			cout << answer << '\n';
		cout << line;
	}
}