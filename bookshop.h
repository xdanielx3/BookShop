/* Daniel Kovalevski 204363204
   Max Neviantsev 317497337 */
#ifndef _BOOKSHOP
#define _BOOKSHOP
#include <iostream>
#include <string>
#include "database.h"
using namespace std;

class bookshop {
private:
	static bookshop* bshop;
	bookshop() {}
	bookshop(bookshop& bs) {}
	
public:
	static bookshop* instance() {
		if (bshop == 0) bshop = new bookshop;
		return bshop;
	}
	void print_all_books_in_stock();
	void print_all_orders();
	void print_all_customers();
	void print_all_suppliers();
	void print_transactions_between_dates();
	void print_all_books_with_discount();
	void check_if_book_in_stock();
	void check_book_suppliers();
	void how_many_copies_sold_since();
	void how_many_books_customer_bought_since();
	void customer_who_bought_the_most_books();
	void supplier_from_whome_most_books_were_ordered();
	void how_many_orders_where_made();
	void how_many_orders_have_been_sold();
	void how_much_discount_customer_got();
	void quarter_earnings();
	void how_many_customers_joined_since();
	void total_orders_from_suppliers_cost();
	void how_many_books_sold_by_employee();
	void best_sellers();
};

bookshop* bookshop::bshop = 0;

//FUNCTIONS

//1
void bookshop::print_all_books_in_stock() {
	Database& db = Database::getInstance();
	Connection* con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM books WHERE stock != 0;");
	ResultSet *rset = pstmt->executeQuery();
	rset->first();
	cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~" << endl << "Books in stock:" << endl;
	do {
		cout << " - " << rset->getString("book_name") << endl;
	} while (rset->next());
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//2
void bookshop::print_all_orders() {
	Database& db = Database::getInstance();
	Connection* con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM orders WHERE order_status != 'Delivered';");
	ResultSet *rset = pstmt->executeQuery();
	rset->first();
	cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << "Orders and their status:" << endl;
	cout << " Order Date\t Customer #\t Book #\t Order Status" << endl << endl;
	do {
		cout << " - " <<  rset->getString("order_date") << "  \t\t" <<
			rset->getString("customer_number") << "   \t     " <<
			rset->getString("book_id") << "\t  " <<
			rset->getString("order_status") << endl;
	} while (rset->next());
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//3
void bookshop::print_all_customers() {
	Database& db = Database::getInstance();
	Connection* con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM customers;");
	ResultSet *rset = pstmt->executeQuery();
	rset->first();
	cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << "Our Customers:" << endl;
	cout << "Customer#\t Name" << endl;
	do {
		cout << " - " << rset->getString("customer_number") << "\t \t " <<
			rset->getString("first_name") << " " <<
			rset->getString("last_name") << endl;
	} while (rset->next());
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//4
void bookshop::print_all_suppliers() {
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM suppliers;");
	ResultSet *rset = pstmt->executeQuery();
	rset->first();
	cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << "Suppliers:" << endl;
	do {
		cout << " - " << rset->getInt("supplier_id") << "\t" << rset->getString("supplier_name") << endl;
	} while (rset->next());
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//5
void bookshop::print_transactions_between_dates() {
	string date_1, date_2;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM transactions inner join customers on customers.customer_number = transactions.customer_number inner join books on books.book_id = transactions.book_id WHERE transaction_date >= ? AND transaction_date <= ?;");
	cout << endl << "Type the start date [yyyy-mm-dd]: ";
	cin.ignore(1000, '\n');
	getline(cin, date_1);
	pstmt->setString(1, date_1);
	cout << endl << "Type the end date [yyyy-mm-dd]: ";
	getline(cin, date_2);
	pstmt->setString(2, date_2);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << "Transactions between " << date_1 << " and " << date_2 << ":" << endl;
		cout << " Transaction Date\t Customer\t\t Book\t" << endl << endl;
		do {
			cout << " - " << rset->getString("transaction_date") << "\t\t" <<
				rset->getString("first_name") << " " << rset->getString("last_name") << "\t\t" <<
				rset->getString("book_name") << endl;
		} while (rset->next());
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	}
	else
		cout << "No transactions between those dates" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//6
void bookshop::print_all_books_with_discount() {
	Database& db = Database::getInstance();
	Connection* con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM books WHERE discount > 0");
	ResultSet *rset = pstmt->executeQuery();
	rset->first();
	cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << "Books on discount:" << endl;
	cout << " Book Name\t\t Price\t Discount" << endl << endl;
	do {
		cout << " - " << rset->getString("book_name") << " \t \t " <<
			rset->getString("price") << "$\t " <<
			rset->getString("discount") << endl;
	} while (rset->next());
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//7
void bookshop::check_if_book_in_stock() {
	string book_name;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM books WHERE book_name = ?;");
	cout << endl << "Type the name of the book:\t";
	cin.ignore(1000, '\n');
	getline(cin, book_name);
	pstmt->setString(1, book_name);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		if (rset->getInt("stock"))
			cout << "There's " << rset->getInt("stock") << " copies of " << book_name << endl << endl;
		else
			cout << "The book is not in stock but you can order it" << endl << endl;
	}
	else
		cout << "Book doesnt exist" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//8
void bookshop::check_book_suppliers() {
	string book_name;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM suppliers inner join sup_books on sup_books.supplier_id = suppliers.supplier_id inner join books on books.book_id = sup_books.book_id where book_name = ?;");
	cout << endl << "Type the name of the book: ";
	cin.ignore(1000, '\n');
	getline(cin, book_name);
	pstmt->setString(1, book_name);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << "Supplier id\t Supplier name" << endl;
		do {
			cout << " - " << rset->getInt("supplier_id") << "\t\t" << rset->getString("supplier_name") << endl;
		} while (rset->next());
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	}
	else
		cout << "There's no suppliers supplying this book" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//9
void bookshop::how_many_copies_sold_since() {
	string book_name, date;
	int count = 0;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM transactions inner join books on transactions.book_id = books.book_id WHERE book_name = ? AND transaction_date >= ?;");
	cout << endl << "Type the name of the book:\t";
	cin.ignore(1000, '\n');
	getline(cin, book_name);
	pstmt->setString(1, book_name);
	cout << endl << "Since? [yyyy-mm-dd]: ";
	getline(cin, date);
	pstmt->setString(2, date);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		do {
			count++;
		} while (rset->next());
	}
	cout << endl << count << " copies of " << book_name << " sold since " << date << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//10
void bookshop::how_many_books_customer_bought_since() {
	string first_name, last_name, date;
	int count = 0;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM transactions inner join customers on transactions.customer_number = customers.customer_number WHERE first_name = ? AND last_name = ?  AND transaction_date >= ?;");
	cout << endl << "Customers first name:\t";
	cin.ignore(1000, '\n');
	getline(cin, first_name);
	pstmt->setString(1, first_name);
	cout << endl << "Customers last name:\t";
	getline(cin, last_name);
	pstmt->setString(2, last_name);
	cout << endl << "Since? [yyyy-mm-dd]: ";
	getline(cin, date);
	pstmt->setString(3, date);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		do {
			count++;
		} while (rset->next());
	}
	cout << endl << first_name << " " << last_name << " bought " << count << " books since " << date << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//11
void bookshop::customer_who_bought_the_most_books() {
	string date;
	int tmp;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT customer_number, sum(amount) FROM transactions where transaction_date >= ? group by customer_number order by sum(amount) desc;");
	cout << endl << "Since? [yyyy-mm-dd]: ";
	cin.ignore(1000, '\n');
	getline(cin, date);
	pstmt->setString(1, date);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		tmp = rset->getInt("customer_number");
		cout << " Customer numbers of the most buying customers since " << date << ": ";
		do {
			cout << rset->getInt("customer_number") << " ";
		} while ((rset->next()) && (rset->getInt("sum(amount)") == tmp));
		cout << endl << endl;
	}
	else
		cout << "There were no sales on those dates" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//12
void bookshop::supplier_from_whome_most_books_were_ordered() {
	int tmp;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT book_id, sum(amount) FROM orders group by book_id order by sum(amount) desc;");
	ResultSet *rset = pstmt->executeQuery();
	rset->first();
	tmp = rset->getInt("book_id");
	delete pstmt;
	delete rset;
	pstmt = con->prepareStatement("SELECT * FROM sup_books WHERE book_id = ?;");
	pstmt->setInt(1, tmp);
	rset = pstmt->executeQuery();
	rset->first();
	cout << " Supplier's ID from whome the most books were ordered: " << rset->getInt("supplier_id") << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//13
void bookshop::how_many_orders_where_made() {
	string date_1, date_2;
	int count = 0;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM orders WHERE order_date >= ? AND order_date <= ?;");
	cout << endl << "Type the start date [yyyy-mm-dd]: ";
	cin.ignore(1000, '\n');
	getline(cin, date_1);
	pstmt->setString(1, date_1);
	cout << endl << "Type the end date [yyyy-mm-dd]: ";
	getline(cin, date_2);
	pstmt->setString(2, date_2);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		do {
			count++;
		} while (rset->next());
	}
	cout << endl << count << " orders where made between " << date_1 << " and " << date_2 << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//14
void bookshop::how_many_orders_have_been_sold() {
	string date_1, date_2;
	int count = 0;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM orders WHERE order_status = 'Delivered' AND order_date >= ? AND order_date <= ?;");
	cout << endl << "Type the start date [yyyy-mm-dd]: ";
	cin.ignore(1000, '\n');
	getline(cin, date_1);
	pstmt->setString(1, date_1);
	cout << endl << "Type the end date [yyyy-mm-dd]: ";
	getline(cin, date_2);
	pstmt->setString(2, date_2);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		do {
			count++;
		} while (rset->next());
	}
	cout << endl << count << " orders where eventually sold between " << date_1 << " and " << date_2 << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//15
void bookshop::how_much_discount_customer_got() {
	string date, first_name, last_name;
	double discount = 0;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM transactions inner join books on books.book_id = transactions.book_id inner join customers on customers.customer_number = transactions.customer_number WHERE first_name = ? AND last_name = ? AND transaction_date >= ?;");
	cout << endl << "Customer's first name: ";
	cin.ignore(1000, '\n');
	getline(cin, first_name);
	pstmt->setString(1, first_name);
	cout << endl << "Customer's last name: ";
	getline(cin, last_name);
	pstmt->setString(2, last_name);
	cout << endl << "Since [yyyy-mm-dd]: ";
	getline(cin, date);
	pstmt->setString(3, date);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		do {
			discount += rset->getInt("discount");
		} while (rset->next());
	}
	cout << endl << "Total discount " << first_name << " " << last_name << " had since " << date << ":\t" << discount << "$" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//16
void bookshop::quarter_earnings() {
	string year1, year2, q1s = "-01-01", q1e = "-03-31", q2s = "-04-01", q2e = "-06-31", q3s = "-07-01", q3e = "-09-31", q4s = "-10-01", q4e = "-12-31";
	int Q;
	double earnings = 0;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM transactions inner join books on transactions.book_id = books.book_id WHERE transaction_date >= ? AND transaction_date <= ?;");
	cout << endl << "Type the year to analyze: ";
	cin.ignore(1000, '\n');
	getline(cin, year1);
	year2 = year1;
	cout << endl << "Type the quarter number [1-4] to analyze: ";
	cin >> Q;
	switch (Q)
	{
	case 1:
		year1.append(q1s);
		year2.append(q1e);
		break;
	case 2:
		year1.append(q2s);
		year2.append(q2e);
		break;
	case 3:
		year1.append(q3s);
		year2.append(q3e);
		break;
	case 4:
		year1.append(q4s);
		year2.append(q4e);
		break;
	default:
		cout << "Something went wrong" << endl;
	}
	pstmt->setString(1, year1);
	pstmt->setString(2, year2);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		do {
			earnings += rset->getInt("price");
		} while (rset->next());
	}
	cout << endl << "The shop earned during Q"<< Q << " " << earnings << "$" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//17
void bookshop::how_many_customers_joined_since() {
	string date;
	int count = 0;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM customers WHERE join_date >= ?;");
	cout << endl << "Customer joined since? [yyyy-mm-dd]: ";
	cin.ignore(1000, '\n');
	getline(cin, date);
	pstmt->setString(1, date);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		do {
			count++;
		} while (rset->next());
	}
	cout << endl << count << " customers joined since " << date << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//18
void bookshop::total_orders_from_suppliers_cost() {
	string date_1, date_2;
	int id;
	double money = 0;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM orders inner join sup_books on sup_books.book_id = orders.book_id WHERE order_date >= ? AND order_date <= ?;");
	cout << endl << "From [yyyy-mm-dd]: ";
	cin.ignore(1000, '\n');
	getline(cin, date_1);
	pstmt->setString(1, date_1);
	cout << endl << "To [yyyy-mm-dd]: ";
	getline(cin, date_2);
	pstmt->setString(2, date_2);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		do {
			money += rset->getInt("price");
		} while (rset->next());
	}
	cout << endl << "Total orders from suppliers cost from " << date_1 << " to " << date_2 << ":\t" << money << "$" << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//19
void bookshop::how_many_books_sold_by_employee() {
	string date_1, date_2, name;
	int count = 0;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM transactions WHERE sold_by = ? AND transaction_date >= ? AND transaction_date <= ?;");
	cout << endl << "Type employee's name: ";
	cin.ignore(1000, '\n');
	getline(cin, name);
	pstmt->setString(1, name);
	cout << endl << "Type the start date [yyyy-mm-dd]: ";
	getline(cin, date_1);
	pstmt->setString(2, date_1);
	cout << endl << "Type the end date [yyyy-mm-dd]: ";
	getline(cin, date_2);
	pstmt->setString(3, date_2);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		do {
			count++;
		} while (rset->next());
	}
	cout << endl << count << " books were sold by " << name << " between " << date_1 << " and " << date_2 << endl << endl;
	delete con;
	delete rset;
	delete pstmt;
}
//20
void bookshop::best_sellers() {
	string date_1, date_2;
	int count = 0;
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	PreparedStatement *pstmt = con->prepareStatement("SELECT book_id,sum(amount) FROM transactions where transaction_date >= ? AND transaction_date <= ? group by book_id order by sum(amount) desc LIMIT 10;");
	cout << endl << "Type the start date [yyyy-mm-dd]: ";
	cin.ignore(1000, '\n');
	getline(cin, date_1);
	pstmt->setString(1, date_1);
	cout << endl << "Type the end date [yyyy-mm-dd]: ";
	getline(cin, date_2);
	pstmt->setString(2, date_2);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->first()) {
		cout << "Best sellers IDs between " << date_1 << " and " << date_2 << ":" << endl;
		do {
			count++;
			cout << count << ". " << rset->getInt("book_id") << endl;
		} while (rset->next());
	}
	else
		cout << "No books were sold on those dates" << endl;
	cout << endl;
	delete con;
	delete rset;
	delete pstmt;
}
#endif // !_BOOKSHOP