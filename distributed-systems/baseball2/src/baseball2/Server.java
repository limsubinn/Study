package baseball2;

import java.io.*;
import java.net.*;
import java.util.*;

public class Server {
	
	private ServerSocket serverSock = null;
	private Socket socket = null;
	
	ArrayList <ChatThread> list = new ArrayList <ChatThread>();
	
	public void start() {
		try {
		
			serverSock = new ServerSocket(5000);
			System.out.println("server start");
			
			while(true) {
			
				socket = serverSock.accept();				
				ChatThread chat = new ChatThread();
	
				list.add(chat);
	
				chat.start();
			}
		} catch(Exception e) {
			System.out.println("[Server] start() Exception 발생!!");
		}   
	} 
	
	public static void main(String[] args) {
		Server server = new Server();
		server.start();
	}
	
	void msgSendAll(String msg) {
		for(ChatThread ct : list) {
			ct.outMsg.println(msg);
		}
	}

	class ChatThread extends Thread {
		
		String message;
		String[] splitMsg;
		
		private BufferedReader inMsg = null;
		private PrintWriter outMsg = null;
		
		public void run() {
		
			Game game;
			game = new Game();
			
			boolean status = true;
			
			System.out.println("##ChatThread start...");
			
			try {

				inMsg = new BufferedReader(new InputStreamReader(socket.getInputStream()));
				outMsg = new PrintWriter(socket.getOutputStream(), true);
				
				int n=0;
				
				int cnt=0;
				boolean val=false;
				String out;
				String cnt1=null;
				int strike, ball;
				
				while(status) {

					message = inMsg.readLine();
					splitMsg = message.split("/");
					
					if(splitMsg[1].equals("logout")) {
						list.remove(this);
						
						msgSendAll("server/" + splitMsg[0] + "님이 로그아웃했습니다.");
						System.out.println("[" + splitMsg[0] + "] logout");
						
						status = false;
					}
					
					else if(splitMsg[1].equals("login")) {
						msgSendAll("server/"+splitMsg[0]+"님이 로그인했습니다.");
						System.out.println("[" + splitMsg[0] + "] login");
					}
					
					else if (splitMsg[1].equals("game start")) {
						msgSendAll("server/"+splitMsg[0]+"님이 게임을 시작하셨습니다. 숫자 3개를 입력하세요.");
						System.out.println("[" + splitMsg[0] + "] game start");
						
						n++;
						
						game.randomInt();
					}
					
					else if (splitMsg[1].equals("quit")) {
						list.remove(this);
						
						msgSendAll("server/" + splitMsg[0] + "님이 종료했습니다.");
						System.out.println("[" + splitMsg[0] + "] quit");
						
						status = false;
					}
		
					else {
						msgSendAll(message);
					}
					
					if (n!=0)
					{
						if (n==1) n++;
						
						else if (splitMsg[1].length() != 3)
						{
							msgSendAll("server/" + splitMsg[1]);
							msgSendAll("server/ [" + splitMsg[0] + "] 숫자를 다시 입력하세요.");
						}
						
						else 
						{
							game.inputUserNumber(splitMsg[1]);
							
							strike=game.getStrike();
						    ball=game.getBall();
						    
						    cnt = game.getCount();
						    if(cnt<10) cnt1="0"+String.valueOf(cnt);
						    else cnt1=String.valueOf(cnt);
						    
						    val = game.getValue();
						    if(val) out = "success";
						    else out = "fail";
						    
						    msgSendAll("server/ [" + splitMsg[0] + "] 게임 현황: " + strike + "S " + ball + "B" + " "+ out +" "+cnt1);
						    
							n++;
							
							
							if (val) {
								msgSendAll("server/" + "Game finish! " + splitMsg[0] + " win!!");
								System.out.println("[" + splitMsg[0] + "] Game finish(win)");
								n=0;
							}
							else if (n==7) {
								msgSendAll("server/ Game finish! " + splitMsg[0] + " lose!!");
								System.out.println("[" + splitMsg[0] + "] Game finish(lose)");
								n=0;
							}
							else {
								msgSendAll("server/ [" + splitMsg[0] + "] 숫자 3개를 입력하세요.");
							}
						}
					}
					
					

				} 
				
				this.interrupt();
				System.out.println("##"+this.getName()+"stop!!");
			} catch(IOException e) {
				list.remove(this);
				System.out.println("[ChatThread] run() IOException 발생!!");
			}
		}
	}
	
}