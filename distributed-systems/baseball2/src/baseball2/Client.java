package baseball2;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;

import javax.swing.*;

public class Client implements ActionListener, Runnable {
    private String ip;
    private String nickname;
    private Socket socket;
    
    private BufferedReader in = null;
    private PrintWriter out = null;

    private JPanel loginJPanel;
    private JPanel logoutJPanel;
    private JButton loginJButton;
    private JButton logoutJButton;
    
    private JLabel nameLabel1;
    private JLabel nameLabel2;
    private JTextField nameInput;

    private JPanel msgJPanel;
    private JTextField msgInput; 
    private JButton exitJButton; 

    private JFrame jframe;
    private JTextArea msgOut;

    private Container container;
    private CardLayout cardLayout;
    
    private Thread thread;

    boolean state; 

    public Client(String ip) {
        this.ip = ip;
        
        loginJPanel = new JPanel();
        loginJPanel.setLayout(new BorderLayout());
        nameInput = new JTextField(15);
       
        loginJButton = new JButton("로그인");
        loginJButton.addActionListener(this);
        
        nameLabel1 = new JLabel("대화명");
        
        loginJPanel.add(nameLabel1, BorderLayout.WEST);
        loginJPanel.add(nameInput, BorderLayout.CENTER);
        loginJPanel.add(loginJButton, BorderLayout.EAST);

        logoutJPanel = new JPanel();
        logoutJPanel.setLayout(new BorderLayout());
        nameLabel2 = new JLabel();
        
        logoutJButton = new JButton("로그아웃");
        logoutJButton.addActionListener(this);
 
        logoutJPanel.add(nameLabel2, BorderLayout.CENTER);
        logoutJPanel.add(logoutJButton, BorderLayout.EAST);

        msgJPanel = new JPanel();
        msgJPanel.setLayout(new BorderLayout());
        msgInput = new JTextField(30);
        
        msgInput.addActionListener(this);
        
        exitJButton = new JButton("종료");
        exitJButton.addActionListener(this);
  
        msgJPanel.add(msgInput, BorderLayout.CENTER);
        msgJPanel.add(exitJButton, BorderLayout.EAST);

        container = new JPanel();
        cardLayout = new CardLayout();
        container.setLayout(cardLayout);
        container.add(loginJPanel, "login");
        container.add(logoutJPanel, "logout");

        jframe = new JFrame("::숫자 야구 게임::");
        msgOut = new JTextArea("", 10, 30);
        
        msgOut.setEditable(false);
        
        JScrollPane jsp = new JScrollPane(msgOut, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        
        jframe.add(container, BorderLayout.NORTH);
        jframe.add(jsp, BorderLayout.CENTER);
        jframe.add(msgJPanel, BorderLayout.SOUTH);
       
        cardLayout.show(container, "login");
        
        jframe.pack();
        jframe.setResizable(false);
        jframe.setVisible(true);

    }
    
    
    public void connectServer() {
        try {
            socket = new Socket(ip, 5000);

            System.out.println("[Client] Server 연결 성공!!");
            
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            out = new PrintWriter(socket.getOutputStream(), true);
           
            out.println(nickname+"/"+"login");
            
            thread = new Thread(this);

            thread.start();
        } catch(Exception e) {
            System.out.println("[Client] connectServer() Exception 발생!!");
        }
    }

    public void actionPerformed(ActionEvent arg0) {
        Object obj = arg0.getSource();

        if(obj == exitJButton) {
            out.println(nickname + "/" + "quit");
            
            System.exit(0);
        } 
        
        else if(obj == loginJButton) {
       
            nickname = nameInput.getText();
            nameLabel2.setText("대화명 : " + nickname);
           
            cardLayout.show(container, "logout");

            connectServer();
            
        } 
        
 
        else if(obj == logoutJButton) {
        	
            out.println(nickname + "/" + "logout");
            msgOut.setText("");
            
            cardLayout.show(container, "login");
            
            out.close();            
            try {
                in.close();
                socket.close();
            } catch(IOException e) {
                e.printStackTrace();
            }
            
            state = false;
        } 
        
        else if(obj == msgInput) {
            out.println(nickname + "/" + msgInput.getText());
            msgInput.setText("");
        }
    }

    public void run() {
    
        String msg;
        String[] rmsg;
        
        state = true;
        
        while(state) {
            try {
        
                msg = in.readLine();
                rmsg = msg.split("/");
                
                msgOut.append(rmsg[0] + ">"+rmsg[1] + "\n");
                msgOut.setCaretPosition(msgOut.getDocument().getLength());
            
            } catch(IOException e) {
                state = false;
            }
        }
        
        System.out.println("[Client] " + thread.getName() + " 종료");
    }

    public static void main(String[] args) {
        Client mcc = new Client("localhost");
    }
}
