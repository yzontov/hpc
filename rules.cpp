#include "include/rules.h"

    Rule::Rule(unsigned char Agents, unsigned char Alternatives) : Agents(Agents), Alternatives(Alternatives), m(Alternatives) { }

    CC Rule::plurality(unsigned int profile[]) //Plurality ������ ���������
    {
        std::vector<int> amounts(Alternatives);
        //������������� ������

        //������� ��������� ������ ����
        for (int i = 0; i < Agents; i++)
        {
            int kk = (int)m[profile[i]][0];
            //std::cout << kk << std::endl;
            amounts[kk - 1]++;
        }


        //������� ���������
        int max = *(std::max_element(amounts.begin(), amounts.end()));

        CC result;
        for (char i = 0; i < Alternatives; i++)
        {
            if (amounts[i] == max)
                result.push_back(i + 1);
        }

        return result;
    }

    CC Rule::hare(unsigned int profile[])
    {
        int omitted = 0; //���������� ����������� �����������
        //�������� �� ������������ ��� ���������
        std::vector<bool> exist(Alternatives, true);

        int min; //�������
        int kol; //���������� �����������

        while (omitted < Alternatives)            //������������� ����
        {
            std::vector<int> amounts(Alternatives);

            for (int i = 0; i < Agents; i++)
                for (int j = 0; j < Alternatives; j++)
                {
                    int kk = (int)m[profile[i]][j] - 1;
                    if (exist[kk])
                    {
                        amounts[kk]++;
                        break;
                    }
                }
            min = Alternatives * Agents;
            for (int i = 0; i < Alternatives; i++)
                if (exist[i] && amounts[i] < min) min = amounts[i];
            kol = 0;
            for (int i = 0; i < Alternatives; i++)
                if (amounts[i] == min && exist[i]) kol++;
            if (kol == Alternatives - omitted) break;
            else
            {
                for (int i = 0; i < Alternatives; i++)
                    if (amounts[i] == min) exist[i] = false;
                omitted += kol;
            }
        }
        //������� ���������� �� ������ ���������� �����������
        CC result;
        for (char i = 0; i < Alternatives; i++)
        {
            if (exist[i])
                result.push_back(i + 1);
        }

        return result;
    }

    CC Rule::approval2(unsigned int profile[]) {
        //������������� ������
        std::vector<int> amounts(Alternatives);

        //������� ��������� ������ ����
        for (int i = 0; i < Agents; i++)
        {
            for (int j = 0; j < 2; j++) {
                int kk = (int)m[profile[i]][j];
                amounts[kk - 1]++;
            }
        }

        //������� ���������
        int max = *(std::max_element(amounts.begin(), amounts.end()));

        CC result;
        for (char i = 0; i < Alternatives; i++)
        {
            if (amounts[i] == max)
                result.push_back(i + 1);
        }

        return result;
    }

    CC Rule::borda(unsigned int profile[])
    {
        //������������� ������
        std::vector<int> amounts(Alternatives);

        for (int i = 0; i < Agents; i++)
        {
            for (int j = 0; j < Alternatives; j++) {
                int kk = (int)m[profile[i]][j];
                amounts[kk - 1] += (Alternatives - j - 1);
            }

        }

        //������� ���������
        int max = *(std::max_element(amounts.begin(), amounts.end()));

        CC result;
        for (char i = 0; i < Alternatives; i++)
        {
            if (amounts[i] == max)
                result.push_back(i + 1);
        }

        return result;
    }

    CC Rule::nanson_multy(unsigned int profile[])
    {

        int omitted = 0; //���������� ����������� �����������
        //�������� �� ������������ ��� ���������
        std::vector<bool> exist(Alternatives, true);

        int current; //������� ���������� ���������� �����������            
        int sum; //����� ���� ����� r()
        int kol; //���������� ����������
        double average; //������� ����� ����� (r � ������)

        while (omitted < Alternatives)            //������������� ����
        {
            std::vector<int> amounts(Alternatives);//������������� ������

            for (int i = 0; i < Agents; i++)  //������� ����� �����
            {
                current = 0;
                for (int j = Alternatives - 1; j >= 0; j--) {
                    int kk = (int)m[profile[i]][j] - 1;
                    if (exist[kk])
                    {
                        amounts[kk] += current;
                        current++;
                    }
                }
            }
            sum = 0;
            for (int i = 0; i < Alternatives; i++)
                if (exist[i]) sum += amounts[i];
            average = (sum * 1.0) / (double)(Alternatives - omitted); //������� ��������

            kol = 0;
            for (int i = 0; i < Alternatives; i++)
                if (amounts[i] < average && exist[i]) kol++;
            if (kol == 0) break;
            else
            {
                for (int i = 0; i < Alternatives; i++)
                    if (amounts[i] < average && exist[i]) exist[i] = false;
                omitted += kol;
            }
        }
        //������� ���������� �� ������ ���������� �����������
        CC result;
        for (char i = 0; i < Alternatives; i++)
        {
            if (exist[i])
                result.push_back(i + 1);
        }

        return result;
    }

    CC Rule::treshold(unsigned int profile[]) //��������� �������
    {
        std::vector<std::vector<int> > amounts2(
            Alternatives,
            std::vector<int>(Alternatives));
        //�������������� ������

        //������������ ���������� ��������� ����
        for (int i = 0; i < Agents; i++)
            for (int j = 0; j < Alternatives; j++) {
                int kk = (int)m[profile[i]][j] - 1;
                amounts2[kk][j]++;
            }


        //�������� �� ������������ ��� ���������
        std::vector<bool> exist(Alternatives, true);

        int min;
        for (int i = Alternatives - 1; i >= 0; i--)  //���� �� ������� ����, ������� � ����������
        {
            min = Agents;
            //���� ������� �� ���������� ��������� �� i-� ����� ����� ��� �� �������� �����������
            for (int j = 0; j < Alternatives; j++)
                if (exist[j] && amounts2[j][i] < min)
                    min = amounts2[j][i];
            //���������� ���������� ������������, � ������� ���������� i-� ���� ������ ������������ ����� ����������
            for (int j = 0; j < Alternatives; j++)
                if (exist[j] && amounts2[j][i] > min)
                    exist[j] = false;
        }
        CC result;
        for (char i = 0; i < Alternatives; i++)
        {
            if (exist[i])
                result.push_back(i + 1);
        }

        return result;
    }

    CC Rule::approval3(unsigned int profile[]) {
        //������������� ������
        std::vector<int> amounts(Alternatives);

        //������� ��������� ������ ����
        for (int i = 0; i < Agents; i++)
        {
            for (int j = 0; j < 3; j++) {
                int kk = (int)m[profile[i]][j];
                amounts[kk - 1]++;
            }
        }

        //������� ���������
        int max = *(std::max_element(amounts.begin(), amounts.end()));

        CC result;
        for (char i = 0; i < Alternatives; i++)
        {
            if (amounts[i] == max)
                result.push_back(i + 1);
        }

        return result;
    }

    CC Rule::condorcet(unsigned int profile[]) {
        std::vector<std::vector<int> > majorityMatrix(
            Alternatives,
            std::vector<int>(Alternatives));

        std::vector<bool> isUndominated(Alternatives, true);
        //for (int i = 0; i < Alternatives; i++)
         //   for (int j = 0; j < Alternatives; j++)
         //       majorityMatrix[i, j] = 0;

        for (int i = 0; i < Agents; i++)
            for (int j = 0; j < Alternatives - 1; j++)
                for (int k = j + 1; k < Alternatives; k++) {
                    int kk1 = (int)m[profile[i]][j];
                    int kk2 = (int)m[profile[i]][k];
                    majorityMatrix[kk1-1][kk2-1]++;
                }

        for (int i = 0; i < Alternatives; i++) majorityMatrix[i][i] = 0;
        for (int i = 0; i < Alternatives - 1; i++)
            for (int j = i + 1; j < Alternatives; j++)
                if (majorityMatrix[i][j] > majorityMatrix[j][i])
                {
                    majorityMatrix[i][j] = 1;
                    majorityMatrix[j][i] = -1;
                }
                else if (majorityMatrix[i][j] < majorityMatrix[j][i])
                {
                    majorityMatrix[i][j] = -1;
                    majorityMatrix[j][i] = 1;
                }
                else
                {
                    majorityMatrix[i][j] = 0;
                    majorityMatrix[j][i] = 0;
                }
        //������� �������������� �����������

        for (int i = 0; i < Alternatives; i++)
            for (int j = 0; j < Alternatives; j++)
                if (majorityMatrix[j][i] == 1)
                {
                    isUndominated[i] = false;
                    break;
                }

        CC result;
        for (char i = 0; i < Alternatives; i++)
        {
            if (isUndominated[i])
                result.push_back(i + 1);
        }

        return result;
    }

    CC Rule::black(unsigned int profile[]) {
        CC res = condorcet(profile);
        if (res.size() > 0)
            return res;
        else
            return borda(profile);
    }

    CC Rule::inverse_plurality(unsigned int profile[]) {
        std::vector<int> amounts(Alternatives);
        //������������� ������


        for (int i = 0; i < Agents; i++)
        {

            int kk = (int)m[profile[i]][Alternatives - 1];
            //std::cout << kk << std::endl;
            amounts[kk - 1]++;
        }


        int min = *(std::min_element(amounts.begin(), amounts.end()));

        CC result;
        for (char i = 0; i < Alternatives; i++)
        {
            if (amounts[i] == min)
                result.push_back(i + 1);
        }

        return result;
    }

    CC Rule::inverse_borda(unsigned int profile[]) {
        //������������� ������


        int omitted = 0; //���������� ����������� �����������
        //�������� �� ������������ ��� ���������
        std::vector<int> exist(Alternatives, true);

        int current; //������� ���������� ���������� �����������            
        int min; //�������
        int kol; //���������� �����������

        while (omitted < Alternatives)            //������������� ����
        {
            std::vector<int> amounts(Alternatives);
            for (int i = 0; i < Agents; i++)
            {
                current = 0;
                for (int j = Alternatives - 1; j >= 0; j--)
                {
                    int kk = (int)m[profile[i]][j];
                    if (exist[kk - 1])
                    {
                        amounts[kk - 1] += current;
                        current++;
                    }
                }

            }
            min = Alternatives * Agents;
            for (int i = 0; i < Alternatives; i++)
                if (exist[i] && amounts[i] < min) min = amounts[i];
            kol = 0;
            for (int i = 0; i < Alternatives; i++)
                if (amounts[i] == min && exist[i]) kol++;
            if (kol == Alternatives - omitted) break;
            else
            {
                for (int i = 0; i < Alternatives; i++)
                    if (amounts[i] == min) exist[i] = false;
                omitted += kol;
            }
        }

        CC result;
        for (char i = 0; i < Alternatives; i++)
        {
            if (exist[i])
                result.push_back(i + 1);
        }

        return result;
    }

    CC Rule::coombs(unsigned int profile[])
    {
        int omitted = 0; //���������� ����������� �����������
        //�������� �� ������������ ��� ���������
        std::vector<bool> exist(Alternatives, true);

        std::vector<int> amounts(Alternatives);

        int max; //��������
        int kol; //���������� ������������

        while (omitted < Alternatives)            //������������� ����
        {

            for (int i = 0; i < Agents; i++)
                for (int j = Alternatives - 1; j >= 0; j--) {
                    int kk = (int)m[profile[i]][j];
                    if (exist[kk - 1])
                    {
                        int kk = (int)m[profile[i]][j];
                        amounts[kk - 1]++;
                        break;
                    }
                }
            max = 0;
            for (int i = 0; i < Alternatives; i++)
                if (exist[i] && amounts[i] > max) max = amounts[i];
            kol = 0;
            for (int i = 0; i < Alternatives; i++)
                if (amounts[i] == max && exist[i]) kol++;
            if (kol == Alternatives - omitted) break;
            else
            {
                for (int i = 0; i < Alternatives; i++)
                    if (amounts[i] == max) exist[i] = false;
                omitted += kol;
            }
        }
        //������� ���������� �� ������ ���������� �����������
        CC result;
        for (char i = 0; i < Alternatives; i++)
        {
            if (exist[i])
                result.push_back(i + 1);
        }

        return result;
    }


