/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Byung Jeon
 * Date        : September 17, 2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
	 PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_(limit) {
		for(int i = 0; i <= limit; i++)
		sieve();
	}

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};


void PrimesSieve::display_primes() const {
const int max_primes_width = num_digits(max_prime_),
		  primes_per_row = 80 / (max_primes_width +1);

		cout << endl << "Number of primes found: " << num_primes_ << endl;
		cout << "Primes up to " << limit_ << ":" << endl;

		if(num_primes_ <= primes_per_row){
			for(int i=0; i<=limit_; i++){
				if(is_prime_[i]){
					if(i!=max_prime_){
						cout << i << " ";
					}
					else cout << i << endl;
				}

			}
		}

		else{
			int counter=1;
			for(int i=0; i <= limit_; i++){
				if(is_prime_[i]){
					if(counter!=primes_per_row){
						if(i != max_prime_){
							cout << setw(max_primes_width) << i<<" ";
							counter++;
						}else{
							cout << setw(max_primes_width) << i;
							counter++;
						}
					}
					else{
						cout << setw(max_primes_width) << i << endl;
						counter=1;
					}
				}
			}
		}
	}

	int PrimesSieve::count_num_primes() const {
		int count_num=0;
		for(int i = 2; i<=limit_; i++){
			if(is_prime_[i]){
				count_num++;
			}
		}
		return count_num;
	}


	void PrimesSieve::sieve() {
		for(int i = 2; i <= limit_; i++){
			is_prime_[i] = true;
			for(int i = 2; i < sqrt(limit_); i++){
				if(is_prime_[i]){
					for(int j = i*i; j <= limit_; j = j + i){
						is_prime_[j] = false;
					}
				}
			}
		}

	num_primes_ = count_num_primes();
		for(int i = limit_; i >= 2; i--){
			if(is_prime_[i]){
				max_prime_ = i;
				break;
			}
		}
	}


	int PrimesSieve::num_digits(int num) {
		int numDig = 0;
		while(num != 0){
			num = num / 10;
			numDig++;
		}
		return numDig;
	}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve x(limit);
	x.display_primes();

    return 0;
}
