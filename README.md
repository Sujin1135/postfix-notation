# postfix-notation
It's a description and example of postfix-notation.

Stack은 LIFO(Last In First Out)의 구조를 가지고 있어 마지막에 push한 값이 가장 먼저 출력됩니다.
예를 들어 아래와 같은 동작이 Stack에서 일어났다고 가정해 보겠습니다.

push(5);
push(1);
pop();
push(8);
pop();
push(2);

* push : 입력, pop : 출력

이후에 Stack에 남은 값들은 5, 2 가 될 것입니다. 이유는 pop 이전에 입력된 1과 8은 이미 출력이 되었기 때문입니다. 나중에 입력된 값이 가장 먼저 출력되는 Stack의 구조를 이용하여 중위 표기법에서 후위 표기법으로 변환하는 메서드를 구현할 수 있습니다.

우리는 스택 자료구조를 활용하여 중위 표기법을 넣으면 후위 표기법이 반환되는 함수를 구현할 수 있습니다.

실제 아래의 코드를 실행시킬 경우 "( 5 + 3 ) / 2" 를 "5 3 + 2 /" 로 출력합니다.
