CREATE DATABASE Bankkk;
USE Bankkk;
CREATE TABLE accounts(
id INT AUTO_INCREMENT PRIMARY KEY,
 name VARCHAR(100) NOT NULL,
 email_id VARCHAR(150) NOT NULL
)AUTO_INCREMENT=10000;
INSERT INTO accounts (name,email_id) VALUES("atharva sal","atharvasalunke0p@gmail.com");
INSERT INTO accounts(name,email_id)VALUES("jack","jack100@gmail.com");
SELECT*FROM accounts;

CREATE TABLE P_P(
id INT,
constraint chk_min_id CHECK (id>=10000),
password INT,
pin INT,
CONSTRAINT FK_ID_P FOREIGN KEY (id)REFERENCES accounts(id) ON DELETE CASCADE 
);
INSERT INTO P_P VALUES(10001,525215,1415);
-- ERROR WILL HAPPEN DUE TO CONSTRAINT NOT MEETING THE INPUT VALUE AND INSERTIONS WILL NOT TAKE PLACE
INSERT INTO p_p VALUES(1000,5252167,2515);		
ALTER TABLE P_P MODIFY id INT PRIMARY KEY;
-- INSERT INTO P_P VALUES(10001,52215,1511);
SELECT*FROM P_P;

CREATE TABLE transcation_history(
id INT,
amount INT NOT NULL,
mode VARCHAR(50),
curr_balance INT,
curr_dt VARCHAR(50),
CONSTRAINT FK_TH FOREIGN KEY(id) references accounts(id) ON DELETE CASCADE
);
ALTER TABLE accounts MODIFY email_id VARCHAR(100) UNIQUE;
ALTER TABLE transcation_history MODIFY mode VARCHAR(50) AFTER ID;
ALTER TABLE transcation_history MODIFY amount INT AFTER mode;
ALTER TABLE transcation_history MODIFY curr_dt TIMESTAMP DEFAULT CURRENT_TIMESTAMP; 
INSERT INTO transcation_history (id,mode,amount,curr_balance)VALUES(10000,"Deposit",5126,62376);
INSERT INTO transcation_history (id,mode,amount,curr_balance) VALUES(10001,"Dposit",5126,62376);
INSERT INTO transcation_history  (id,mode,amount,curr_balance)VALUES(10000,"Dposit",5126,62376);
INSERT INTO transcation_history  (id,mode,amount,curr_balance)VALUES(10000,"Dposit",5126,62376);
INSERT INTO transcation_history  (id,mode,curr_balance)VALUES(10000,"Dposit",62376);
-- SORTS THE rows ON ID first in ASC  if id's are same then it sorts rows based on curr_dt in desc 
SELECT *FROM transcation_history ORDER BY id ASC, curr_dt DESC;
  
SELECT *FROM TRANSCATION_HISTORY;
ALTER TABLE P_P MODIFY password VARCHAR(100);
ALTER TABLE P_P MODIFY pin VARCHAR(100);
SET SQL_SAFE_UPDATES =0;
DELETE FROM accounts;
DELETE FROM p_p;
DELETE FROM transcation_history;
ALTER TABLE accounts AUTO_INCREMENT=10000;