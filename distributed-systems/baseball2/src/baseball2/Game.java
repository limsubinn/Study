package baseball2;

import java.util.*;

class Game{
	public static int NUM = 3; 
	public static int CHANCE = 5; 
	int strike=0, ball=0; 
	private boolean val=false;
	private int base[] = new int[NUM]; 
	private int user[] = new int[NUM]; 
	private int cnt=0;
 
	Game(){}

	void randomInt(){ 
		do {
			base[0] = (int)(Math.random()*10);
		} while (base[0]==0);
	 
		for (int i=1; i<base.length; i++) {
			base[i] = (int)(Math.random()*10);
		 
			for (int j=0; j<i; j++) {
				while ((base[i] == base[j]) || (base[i] == 0)) {
					base[i] = (int)(Math.random()*10);
					j=0;
				}
			}
		}

		System.out.println("server creates answer number: " + Arrays.toString(base));
	}
 
	void inputUserNumber(String in1){ 
    
		String in=in1;
		for (int i=0; i<user.length; i++) {
			user[i] = in.charAt(i)-48;
		}
		count(base, user);
 }
 
	synchronized void count(int a[],int b[]){ 
		if (cnt==CHANCE) cnt=0;
		if (val) {val=false; cnt=0;}

		strike=0; ball=0;
		for (int i=0; i<a.length; i++) {
			for (int j=0; j<b.length; j++) {
				if (b[i]==a[j]) {
					if (i==j) strike+=1;
					else ball+=1;
				}
			}
		}
	 
		cnt++;
	 
		if (strike==NUM) val=true;
	}
 
	public int getStrike() {return strike;}
	public int getBall() {return ball;}
 
	int getCount() {return cnt;} 
	boolean getValue() {return val;} 
 
}