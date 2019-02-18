#include <iostream>
//typedef unsigned long uint64_t;
typedef unsigned int uint32_t;
#define N 8
#define F32 0xFFFFFFFF
#define size64 sizeof(uint64_t)
#define ROR(x,n,xsize)((x>>n)|(x<<(xsize-n)))
#define ROL(x,n,xsize)((x<<n)|(x>>(xsize-n)))
#define RKEY(r)((ROR(K,r*3,size64*8))&F32)
const uint64_t K = 0x96EA704CFB1CF672;//base key to forming of round keys
uint32_t RK[N];//massive round keys
void createRoundKeys(bool print)
{
	for (int i = 0; i < N; i++)
	{
		RK[i]=(ROR(K, i * 8, size64 * 8))&F32;
		if (print)
			std::cout << "key[" << i << "]=" << std::hex << RK[i] << std::endl;
	}
}
uint32_t F(uint32_t subblk, uint32_t key)
{
	uint32_t f1 = ROL(subblk, 9, sizeof(subblk) * 8);
	uint32_t f2 = ROR(key, 11, sizeof(key) * 8) | subblk;
	return f1 ^ !f2;
}
//encryption 64-digit block of message
uint64_t encrypt(uint64_t block, bool print)
{
	//select subblocks
	uint32_t left = (block >> 32)&F32;
	uint32_t right = block&F32;

	uint32_t left_, right_;//subblock in the end of round
	for (int r = 0; r < N; r++)
	{
		if (print)
			std::cout << "round " << r << std::endl << "input blks " << std::hex << left << " " << right << std::endl;
		uint32_t fk = F(left, RK[r]);
		left_ = left;
		right_ = right^fk;
		if (r < N - 1)//swap places to next round
		{
			left = right_;
			right = left_;
		}
		else//last round not swap
		{
			left = left_;
			right = right_;
		}
		if (print)
			std::cout << "round" << r << std::endl << "output blks " << std::hex << left << " " << right << std::endl;
	}
	//collect subblock in block
	uint64_t c_block = left;
	c_block = (c_block << 32) | (right&F32);
	return c_block;
}
//decryption 64-digit block of message
uint64_t decrypt(uint64_t c_block, bool print)
{
	//select subblocks
	uint32_t left = (c_block >> 32)&F32;
	uint32_t right = c_block&F32;

	uint32_t left_, right_;//subblock in the end of round
	for (int r = N-1; r >=0; r--)
	{
		if (print)
			std::cout << "round " << r << std::endl << "input blks " << std::hex << left << " " << right << std::endl;
		uint32_t fk = F(left, RK[r]);
		left_ = left;
		right_ = right^fk;
		if (r > 0)//swap places to next round
		{
			left = right_;
			right = left_;
		}
		else //last round not swap
		{
			left = left_;
			right = right_;
		}
		if (print)
			std::cout << "round" << r << std::endl << "output blks " << std::hex << left << " " << right << std::endl;
	}
	//collect subblock in block
	uint64_t block = left;
	block = (block << 32) | (right&F32);
	return block;
}

void main()
{
	std::cout << "C++ Rules" << std::endl;
	std::cout << "Base key\n" <<std::hex<<K<< std::endl;
	std::cout << "\nRound keys:" << std::endl;
	createRoundKeys(false);
	uint64_t msg = 0xFFAADD11CCBB2299;//plain text
	std::cout << "msg:\n" << std::hex << msg << std::endl;
	uint64_t cipher = encrypt(msg, true);//change on true second parameter when debug, ciphertext
	std::cout << "encrypt:\n" << cipher << std::endl;
	msg = decrypt(cipher, true);//change on true second parameter when debug,plain text
	std::cout << "decrypt:\n" << msg<< std::endl;
	system("pause");
}