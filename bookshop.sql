create database if not exists bookshop;
use bookshop;

create table if not exists books (
book_id int unsigned auto_increment primary key,
book_name varchar(20) not null,
author varchar(20) not null,
price int unsigned not null,
discount double unsigned not null,
stock int unsigned not null
);

create table if not exists suppliers (
	supplier_id int unsigned not null auto_increment primary key,
	supplier_name varchar(20) not null
);

create table if not exists sup_books (
	book_id int unsigned not null,
    supplier_id int unsigned not null,
    price int unsigned not null,
    primary key(book_id, supplier_id),
    foreign key(book_id) references books(book_id),
	foreign key(supplier_id) references suppliers(supplier_id)
);

create table if not exists customers (
	customer_number int unsigned not null auto_increment primary key,
    first_name varchar(20) not null,
    last_name varchar(20) not null,
    phone varchar(10) not null
);

create table if not exists transactions (
	transaction_id int unsigned auto_increment not null primary key,
    transaction_date date not null,
    book_id int unsigned not null,
    customer_number int unsigned not null,
    sold_by varchar(20) not null,
    foreign key(book_id) references books(book_id),
    foreign key(customer_number) references customers(customer_number)
); 

create table if not exists orders (
	order_id int unsigned auto_increment not null primary key,
	order_date date not null,    
    book_id int unsigned not null,
    customer_number int unsigned not null,
    foreign key(book_id) references books(book_id),
    foreign key(customer_number) references customers(customer_number)
);

insert into books (book_name, author, price, stock) values ('Gucci Gang', 'Lil Pump', 25, 745);
insert into books (book_name, author, price, stock) values ('ESSKEETIT', 'Lil Pump', 15, 356);
insert into books (book_name, author, price, stock) values ('Mask Off', 'Future', 23, 305);
insert into books (book_name, author, price, stock) values ('Kream', 'Iggy Azalea', 12, 36);
insert into books (book_name, author, price, stock) values ('LOVE', 'Kendrick Lamar', 9, 77);
insert into books (book_name, author, price, stock) values ('Jumpman', 'Drake', 8, 0);
insert into books (book_name, author, price, stock) values ('X', '21 Savage', 11, 130);
insert into books (book_name, author, price, stock) values ('Slippery', 'Migos', 16, 255);
insert into books (book_name, author, price, stock) values ('Humble', 'Kendrick Lamar', 22, 0);
insert into books (book_name, author, price, stock) values ('Kings Dead', 'Jay Rock', 21, 54);

insert into suppliers (supplier_name) values ('Dr. Dre');
insert into suppliers (supplier_name) values ('Snoop Dogg');
insert into suppliers (supplier_name) values ('Ice Cube');
insert into suppliers (supplier_name) values ('Eazy-E');
insert into suppliers (supplier_name) values ('2Pac');
insert into suppliers (supplier_name) values ('NWA');
insert into suppliers (supplier_name) values ('Coolio');
insert into suppliers (supplier_name) values ('Cardi B');
insert into suppliers (supplier_name) values ('Tyga');
insert into suppliers (supplier_name) values ('Post Malone');

insert into customers (first_name, last_name, phone) values ('Sommer', 'Ray', '0509876543');
insert into customers (first_name, last_name, phone) values ('Ana', 'Cherry', '0529876543');
insert into customers (first_name, last_name, phone) values ('Xenia', 'Chumicheva', '0559876543');
insert into customers (first_name, last_name, phone) values ('Sveta', 'Bily', '0549876543');
insert into customers (first_name, last_name, phone) values ('Viki', 'Odintcova', '0509876542');
insert into customers (first_name, last_name, phone) values ('Natalia', 'Barulich', '0509876541');
insert into customers (first_name, last_name, phone) values ('Nastya', 'Nass', '0509876544');
insert into customers (first_name, last_name, phone) values ('Anna', 'Nystrom', '0509876545');
insert into customers (first_name, last_name, phone) values ('Agnes', 'Pimental', '0509876546');
insert into customers (first_name, last_name, phone) values ('Anella', 'Miller', '0509876548');

insert into sup_books (book_id, supplier_id, price) values (1,10,22);
insert into sup_books (book_id, supplier_id, price) values (2,9,12);
insert into sup_books (book_id, supplier_id, price) values (3,8,20);
insert into sup_books (book_id, supplier_id, price) values (4,7,9);
insert into sup_books (book_id, supplier_id, price) values (5,6,6);
insert into sup_books (book_id, supplier_id, price) values (6,5,5);
insert into sup_books (book_id, supplier_id, price) values (7,4,8);
insert into sup_books (book_id, supplier_id, price) values (8,3,13);
insert into sup_books (book_id, supplier_id, price) values (9,2,19);
insert into sup_books (book_id, supplier_id, price) values (10,1,18);
insert into sup_books (book_id, supplier_id, price) values (1,8,22);
insert into sup_books (book_id, supplier_id, price) values (2,5,12);
insert into sup_books (book_id, supplier_id, price) values (3,3,20);

insert into transactions (transaction_date, book_id, customer_number) values ('2018-06-21',1,5);
insert into transactions (transaction_date, book_id, customer_number) values ('2018-06-25',2,1);
insert into transactions (transaction_date, book_id, customer_number) values ('2018-06-26',3,2);
insert into transactions (transaction_date, book_id, customer_number) values ('2018-06-30',4,4);
insert into transactions (transaction_date, book_id, customer_number) values ('2018-07-02',5,3);
insert into transactions (transaction_date, book_id, customer_number) values ('2018-07-04',6,7);
insert into transactions (transaction_date, book_id, customer_number) values ('2018-07-07',7,8);
insert into transactions (transaction_date, book_id, customer_number) values ('2018-07-11',8,10);
insert into transactions (transaction_date, book_id, customer_number) values ('2018-07-16',9,5);
insert into transactions (transaction_date, book_id, customer_number) values ('2018-07-18',10,2);

insert into orders (order_date, book_id, customer_number) values ('2018-06-22',6,4);
insert into orders (order_date, book_id, customer_number) values ('2018-06-25',9,3);
insert into orders (order_date, book_id, customer_number) values ('2018-06-26',6,1);
insert into orders (order_date, book_id, customer_number) values ('2018-06-29',9,10);
insert into orders (order_date, book_id, customer_number) values ('2018-06-30',9,9);
insert into orders (order_date, book_id, customer_number) values ('2018-07-01',9,8);
insert into orders (order_date, book_id, customer_number) values ('2018-07-03',6,2);
insert into orders (order_date, book_id, customer_number) values ('2018-07-05',9,5);
insert into orders (order_date, book_id, customer_number) values ('2018-07-10',6,6);
insert into orders (order_date, book_id, customer_number) values ('2018-07-17',6,7);

ALTER TABLE orders ADD order_status VARCHAR(20);

update orders set order_status = 'ordered' where order_id = 1;
update orders set order_status = 'arived' where order_id = 2;
update orders set order_status = 'customer notified' where order_id = 3;
update orders set order_status = 'customer notified' where order_id = 4;
update orders set order_status = 'ordered' where order_id = 5;
update orders set order_status = 'not ordered' where order_id = 6;
update orders set order_status = 'arived' where order_id = 7;
update orders set order_status = 'customer notified' where order_id = 8;
update orders set order_status = 'arived' where order_id = 9;
update orders set order_status = 'ordered' where order_id = 10;

ALTER TABLE books ADD discount double unsigned not null;

update books set book_name = 'LOVE', author = 'Kendrick Lamar' where book_id = 5;
update customers set first_name = 'Paula', last_name = 'Manzz' where customer_number = 3;
update transactions set transaction_date = '2018-01-01' where transaction_id = 1;
update transactions set transaction_date = '2018-02-15' where transaction_id = 2;
update transactions set transaction_date = '2018-03-08' where transaction_id = 3;
update transactions set transaction_date = '2018-04-22' where transaction_id = 4;
update transactions set transaction_date = '2018-05-16' where transaction_id = 5;
update transactions set transaction_date = '2018-06-17' where transaction_id = 6;
update transactions set transaction_date = '2018-07-09' where transaction_id = 7;
update transactions set transaction_date = '2018-08-26' where transaction_id = 8;
update transactions set transaction_date = '2018-09-30' where transaction_id = 9;
update transactions set transaction_date = '2018-10-15' where transaction_id = 10;
insert into transactions (transaction_date, book_id, customer_number) values ('2018-11-12',6,5);
insert into transactions (transaction_date, book_id, customer_number) values ('2018-12-11',8,2);
insert into orders (order_date, book_id, customer_number, order_status) values ('2018-08-12',8,10, 'Delivered');
insert into orders (order_date, book_id, customer_number, order_status) values ('2018-09-02',9,5, 'Delivered');
insert into orders (order_date, book_id, customer_number, order_status) values ('2018-10-04',10,2, 'Delivered');
ALTER TABLE customers ADD column join_date date not null;
update customers set join_date = '2017-01-05' where customer_number = 1;
update customers set join_date = '2017-02-08' where customer_number = 2;
update customers set join_date = '2017-03-11' where customer_number = 3;
update customers set join_date = '2017-04-22' where customer_number = 4;
update customers set join_date = '2017-05-14' where customer_number = 5;
update customers set join_date = '2017-06-17' where customer_number = 6;
update customers set join_date = '2017-07-30' where customer_number = 7;
update customers set join_date = '2017-08-14' where customer_number = 8;
update customers set join_date = '2017-09-18' where customer_number = 9;
update customers set join_date = '2017-10-02' where customer_number = 10;
ALTER TABLE transactions ADD column sold_by varchar(20) not null;
update transactions set sold_by = 'Travis Scott' where transaction_id = 1;
update transactions set sold_by = 'Travis Scott' where transaction_id = 2;
update transactions set sold_by = 'Lil Jon' where transaction_id = 3;
update transactions set sold_by = 'Travis Scott' where transaction_id = 4;
update transactions set sold_by = 'Lil Jon' where transaction_id = 5;
update transactions set sold_by = 'Travis Scott' where transaction_id = 6;
update transactions set sold_by = 'Lil Jon' where transaction_id = 7;
update transactions set sold_by = 'Lil Jon' where transaction_id = 8;
update transactions set sold_by = 'Travis Scott' where transaction_id = 9;
update transactions set sold_by = 'Lil Jon' where transaction_id = 10;
update transactions set sold_by = 'Travis Scott' where transaction_id = 11;
update transactions set sold_by = 'Lil Jon' where transaction_id = 12;
insert into transactions (transaction_date, book_id, customer_number, sold_by) values ('2018-12-21',4,8,'Lil Jon');
update books set discount = 3 where book_id = 1;
update books set discount = 0 where book_id = 2;
update books set discount = 2 where book_id = 3;
update books set discount = 1 where book_id = 4;
update books set discount = 0 where book_id = 5;
update books set discount = 0 where book_id = 6;
update books set discount = 0 where book_id = 7;
update books set discount = 3 where book_id = 8;
update books set discount = 0 where book_id = 9;
update books set discount = 1 where book_id = 10;
/*inner join books on books.book_id = transactions.book_id WHERE transaction_date >= '01-01-01' AND transaction_date <= '2020-02-02'*/
SELECT * FROM transactions inner join books on books.book_id = transactions.book_id inner join customers on customers.customer_number = transactions.customer_number WHERE first_name = 'viki' AND last_name = 'odintcova' AND transaction_date >= '2018-01-01';