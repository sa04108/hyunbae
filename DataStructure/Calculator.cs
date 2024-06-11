public class Calculator
{
    // char 값이 숫자인지 여부
    public bool IsDigit(char c)
    {
        return c >= '0' && c <= '9';
    }

    // 연산자의 우선순위 반환
    private int GetOpPrec(char op)
    {
        if (op == '*' || op == '/')
            return 5;
        else if (op == '+' || op == '-')
            return 3;
        else if (op == '(')
            return 1;

        return -1;
    }

    // 두 연산자의 우선순위 비교
    private int WhoPrecOp(char op1, char op2)
    {
        int op1Prec = GetOpPrec(op1);
        int op2Prec = GetOpPrec(op2);

        if (op1Prec > op2Prec)
            return 1;
        else if (op1Prec < op2Prec)
            return -1;
        else
            return 0;
    }

    // 중위 표기식을 후위 표기식으로 변환
    // RPN이란 Reverse Polish Notation, 역 폴란드 표기법 즉 후위 표기법을 의미함
    public string ConvToRPNExp(string exp)
    {
        string inf = string.Empty;
        Stack<char> stack = new Stack<char>();
        foreach (var c in exp)
        {
            if (IsDigit(c))
            {
                inf += c;
            }
            else if (c == '(')
            {
                stack.Push(c);
            }
            else if (c == ')')
            {
                while (stack.count > 0 && stack.Peek() != '(')
                {
                    inf += stack.Pop();
                }
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                while (stack.count > 0 && WhoPrecOp(stack.Peek(), c) >= 0)
                {
                    inf += stack.Pop();
                }
                stack.Push(c);
            }
        }

        while (stack.count > 0)
        {
            inf += stack.Pop();
        }

        return inf;
    }

    // 후위 표기식을 계산한 값 반환
    public int EvalRPNExp(string exp)
    {
        Stack<int> stack = new Stack<int>();
        foreach (var c in exp)
        {
            if (IsDigit(c))
            {
                stack.Push(c - '0');
            }
            else
            {
                int op2 = stack.Pop();
                int op1 = stack.Pop();

                switch (c)
                {
                    case '+':
                        stack.Push(op1 + op2);
                        break;
                    case '-':
                        stack.Push(op1 - op2);
                        break;
                    case '*':
                        stack.Push(op1 * op2);
                        break;
                    case '/':
                        stack.Push(op1 / op2);
                        break;
                }
            }
        }

        return stack.Pop();
    }

    // 중위 표기식을 받아 계산한 값 반환
    public int EvalInfixExp(string exp)
    {
        return EvalRPNExp(ConvToRPNExp(exp));
    }
}