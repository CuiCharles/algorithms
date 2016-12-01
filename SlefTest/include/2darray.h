#ifndef ALGO_2D_ARRAY_H__
#define ALGO_2D_ARRAY_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

namespace charles{

	template <typename T=char>
		class Array2D {
		private:
			uint32_t NR;  	// num of row
			uint32_t NC;	// num of column
			T * m_data;		// the place where the array resides;
		public:
			Array2D(uint32_t nrow, uint32_t ncol) {
				NR = nrow;
				NC = ncol;
				m_data = new T[nrow*ncol];
			}

			~Array2D() {
				delete [] m_data;
			}
		private:
			Array2D(const Array2D &);
			Array2D& operator=(const Array2D&);

		public:
			inline const uint32_t row() const { return NR;}
			inline const uint32_t col() const { return NC;}

			inline T& operator() (int row,int col) { return this->m_data[row*NC + col] ;}
			inline const T& operator() ( int row, int col) const{ return this->m_data[row*NC+ col];}
			
			inline T* operator[] (int row) {return &(m_data[row * NC]);}
			inline const T* operator[] (int row) const {return &(m_data[row * NC]);}

			void clear(const T& value) {
				for(uint32_t i = 0;i < NR * NC ;++i) {
					m_data[i] = value;
				}
			}

			//beacause this class is generic, the print format can't be
			//such simple. here just as a demo
			void printArray(){
				for(uint32_t i = 0; i < NR;i++){
					for(uint32_t j = 0; j<NC; j++){
						printf("[%d,%d]:%d ",i,j,m_data[i*NC+j]);
					}
					printf("\n");
				}
			}
		};

		

}

#endif