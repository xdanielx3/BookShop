/* Daniel Kovalevski 204363204
   Max Neviantsev 317497337 */
#include <iostream>
#include "database.h"
#include "bookshop.h"
using namespace std;
//FUNCTIONS
void menu();

int main()
{
	int x;

	do {
		menu();
		cin >> x;
		switch (x){
		case 1:
			bookshop::instance()->print_all_books_in_stock();
			break;
		case 2:
			bookshop::instance()->print_all_orders();
			break;
		case 3:
			bookshop::instance()->print_all_customers();
			break;
		case 4:
			bookshop::instance()->print_all_suppliers();
			break;
		case 5:
			bookshop::instance()->print_transactions_between_dates();
			break;
		case 6:
			bookshop::instance()->print_all_books_with_discount();
			break;
		case 7:
			bookshop::instance()->check_if_book_in_stock();
			break;
		case 8:
			bookshop::instance()->check_book_suppliers();
			break;
		case 9:
			bookshop::instance()->how_many_copies_sold_since();
			break;
		case 10:
			bookshop::instance()->how_many_books_customer_bought_since();
			break;
		case 11:
			bookshop::instance()->customer_who_bought_the_most_books();
			break;
		case 12:
			bookshop::instance()->supplier_from_whome_most_books_were_ordered();
			break;
		case 13:
			bookshop::instance()->how_many_orders_where_made();
			break;
		case 14:
			bookshop::instance()->how_many_orders_have_been_sold();
			break;
		case 15:
			bookshop::instance()->how_much_discount_customer_got();
			break;
		case 16:
			bookshop::instance()->quarter_earnings();
			break;
		case 17:
			bookshop::instance()->how_many_customers_joined_since();
			break;
		case 18:
			bookshop::instance()->total_orders_from_suppliers_cost();
			break;
		case 19:
			bookshop::instance()->how_many_books_sold_by_employee();
			break;
		case 20:
			bookshop::instance()->best_sellers();
			break;
		case 0:
			cout << "Goodbye!" << endl;
			break;
		default:
			cout << "Something went wrong" << endl;
		}
	} while (x);
}

void menu() {
	cout << "MENU:" << endl <<
		"[ 1] Print all the books in stock\t" << "[ 2] Print all the orders" << endl <<
		"[ 3] Print all customers\t\t" << "[ 4] Print all suppliers" << endl <<
		"[ 5] Print transactions between dates\t" << "[ 6] Print all books on discount" << endl <<
		"[ 7] Check if book is in stock\t\t" << "[ 8] Check all suppliers of a book" << endl <<
		"[ 9] Check how many copies sold\t\t" << "[10] check how many books customer bought" << endl <<
		"[11] Customer who bought the most books\t" << "[12] Supplier from whome where ordered the most books" << endl <<
		"[13] Check how many orders where made\t" << "[14] How many orders have been sold" << endl <<
		"[15] Total discount a customer got\t" << "[16] Shop's quarter earnings" << endl <<
		"[17] How many customers joined since\t" << "[18] Total supplier orders cost" << endl <<
		"[19] How many books sold by employee\t" << "[20] Best sellers" << endl;
}