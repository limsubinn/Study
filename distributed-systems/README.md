본 프로젝트는 2021년 1학기, 학부 분산시스템 수업에서 진행된 프로젝트입니다. (2021.05 ~ 2021.06)
<br/>
<br/>

## 💡 프로젝트 설명

### 1) Project Goal
- 본 프로젝트는 소켓프로그래밍을 이용하여 **숫자 야구 게임** 및 **사용자 간 채팅 프로그램**을 구현한다.
프로그램은 server-client 모델을 적용하여 개발되며 client 간 상호적으로 소통이 가능하다.
서버에 연결된 사용자는 채팅 및 숫자 야구 게임을 진행한다. 본 프로젝트의 기능은 접속, 게임진행으로 구성된다.

### 2) 접속
- server 접속 후, 각각의 client는 GUI를 통해 사용하고자 하는 대화명을 입력하여 로그인한다.
- client의 접속이 성공하면 여러 client는 서로 대화를 할 수 있고, 다른 client의 로그인 및 로그아웃 정보를 알 수 있다.
- client는 로그아웃 및 종료 버튼을 누르면 서버에서 나갈 수 있다.

### 3) 게임진행
- client들은 게임시작 전에 채팅을 주고받을 수 있다.
- 채팅 창에 ‘game start’를 입력하면 게임이 시작되고, 이 때 server는 난수 생성을 통해 3자리의 숫자를 설정한다.
- ‘game start’를 입력한 client만 server에게 답안을 전송할 수 있다. (player1)
- player1이 게임을 진행하는 동안 다른 client들은 서로 채팅이 가능하다.
- player1의 게임 진행 상황은 모두에게 공개되기 때문에 다른 client들은 player1에게 힌트를 제공할 수 있다.
- 다른 client들도 ‘game start’를 입력하면 동시에 게임 진행이 가능하다. (하지만 각각의 게임은 별도로 진행된다.)
- player1은 server에게 추측한 3자리의 숫자를 전송한다. 사용되는 숫자는 1~9까지의 서로 다른 숫자이다.
- server은 player1의 숫자와 정답을 비교하여 숫자는 맞지만 위치가 틀렸을 때 ball, 숫자와 위치가 전부 맞으면 strike을 보낸다. 위 결과와 함께 시도횟수(cnt)도 제공한다.
- player1에게 숫자예측 기회는 총 5번 주어진다.
- 게임이 끝난 후에는 다시 채팅을 할 수 있으며, 언제든지 ‘game start’를 통해 또다른 게임을 시작할 수 있다.

<br/>
<br/>

## 💡 클래스 구성

### 1) Client
- 생성자를 통해 GUI를 설정한다.
- 각 패널 화면을 구성한 후에 GUI요소들을 배치한다.
1) connectServer()
: 소켓 객체를 생성하여 ip주소와 port번호를 설정한다. 
: 입출력 스트림을 생성하여 데이터를 주고 받는다.
: 스레드로 여러 client를 관리한다.
2) actionPerformed()
: 액션이벤트를 처리하는 메소드로 GUI의 각 구성요소에 대한 액션들을 처리한다.
: 로그인, 로그아웃, 종료, 채팅입력 - 4개의 구성요소를 클릭했을 때 이벤트들을 처리한다.
3) run()
: 채팅을 주고 받는 기능을 구현한다.

### 2) Server
- 서버 소켓을 생성하고 accept를 이용하여 클라이언트 소켓을 받는다.
- ArrayList를 통해 클라이언트의 스레드를 관리한다.
1) msgSendAll
: ArrayList에 담겨진 client-chat thread들의 채팅창에 메시지를 띄운다.

### 3) ChatThread
- thread를 상속받는 Server class안에 선언된 내부 class이다
1) run()
: 입출력 스트림을 통해 채팅창에 메시지를 띄운다.
: 로그인 ,로그아웃, 종료 이벤트를 포함하여 게임을 진행하는 모든 이벤트를 처리한다.
: Game class에 대한 객체를 생성하고, 해당 객체를 통한 getStrike(),getBall(), getCount(), getValue()를 호출하여 서버에 알려준다.
: 타입의 val (getValue())값에 따라 게임의 결과를 client 채팅창에 출력한다.

### 4) Game
- 게임을 진행하는 class이다.
1) randomInt()
: 숫자 3개를 랜덤으로 생성하는 메소드이다.
: 길이가 3인 배열에 각 숫자를 난수생성하여 저장한다.
: 생성한 숫자를 server에 띄움으로써 사용자는 정답을 확인할 수 있다. 
2) inputUserNumber()
: 사용자 값을 입력 받아 처리하는 함수이다.
: 입력 받은 사용자 값과 정답을 count()의 매개변수로 전달한다.
3) count()
: 사용자에게 입력 받은 숫자와 정답 숫자를 비교하여 strike, ball, cnt 의 값을 결정한다.
: strike가 NUM ,즉 정답일 경우에 val =true로 변경하여 getvalue()를 통해 게임의 결과를 넘겨준다.
4) getStrike(),getBall(), getCount(), getValue()
각각 strike 횟수, ball 횟수, cnt(게임시도) 횟수, val(게임의 결과값)을 넘겨주는 메소드이다.

<br/>
<br/>


## 🔗 Youtube Link
https://youtu.be/xw6bEj2kHq4
<br/>
<br/>

