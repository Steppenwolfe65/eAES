/* The GPL version 3 License (GPLv3)
*
* Copyright (c) 2019 vtdev.com
* This file is part of the CEX Cryptographic library.
*
* This program is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
*
* Implementation Details:
* Test platform for the (RHX/RSX=eAES) symmetric block cipher.
* Contact: develop@vtdev.com */

#include "common.h"
#include "rhx.h"
#include "rhx_kat.h"
#include "sha2_kat.h"
#include "sha3_kat.h"
#include <stdio.h>

/* AES-NI Detection */

#if defined(_MSC_VER)

#include <intrin.h>
#pragma intrinsic(__cpuid)

static int has_aes_ni()
{
	int info[4];
	int mask;
	int val;

	__cpuid(info, 1);

	if (info[2] != 0)
	{
		mask = ((((int)1 << 1) - 1) << 25);
		val = ((info[2] & mask) >> 25);
	}
	else
	{
		val = 0;
	}

	return val;
}

#elif defined(__GNUC__)

#include <cpuid.h>
#pragma GCC target ("ssse3")
#pragma GCC target ("sse4.1")
#pragma GCC target ("aes")
#include <x86intrin.h>

static int has_aes_ni()
{
	int info[4];
	int mask;
	int val;

	if (__get_cpuid(1, &info[0], &info[1], &info[2], &info[3]))
	{
		mask = ((((int)1 << 1) - 1) << 25);
		val = ((info[2] & mask) >> 25);
	}
	else
	{
		val = 0;
	}

	return val;
}

#else

static int has_aes_ni()
{
	return 0;
}

#endif

/**
* \wait for input
*/
void get_response()
{
	wint_t ret;

	ret = getwchar();
}


/* aes and rhx cipher tests */

/**
* \brief Test the CBC mode AES implementations with vectors from Fips197
*/
void test_aes_cbc_fips()
{
	if (aes128_cbc_fips_test() == true)
	{
		printf_s("Success! Passed the FIPS 197 CBC(AES-128) KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the FIPS 197 CBC(AES-128) CBC KAT test. \n");
	}

	if (aes256_cbc_fips_test() == true)
	{
		printf_s("Success! Passed the FIPS 197 CBC(AES-256) CBC KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the FIPS 197 CBC(AES-256) CBC KAT test. \n");
	}
}

/**
* \brief Tests the CTR mode AES implementation with vectors from Fips197
*/
void test_aes_ctr_fips()
{
	if (aes128_ctr_fips_test() == true)
	{
		printf_s("Success! Passed the FIPS 197 CTR(AES-128) KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the FIPS 197 CTR(AES-128) KAT test. \n");
	}

	if (aes256_ctr_fips_test() == true)
	{
		printf_s("Success! Passed the FIPS 197 CTR(AES-256) KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the FIPS 197 CTR(AES-256) KAT test. \n");
	}
}

/**
* \brief Test the ECB mode AES implementation with vectors from Fips197
*/
void test_aes_ecb_fips()
{
	if (aes128_ecb_fips_test() == true)
	{
		printf_s("Success! Passed the FIPS 197 ECB(AES-128) KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the FIPS 197 ECB(AES-128) KAT test. \n");
	}

	if (aes256_ecb_fips_test() == true)
	{
		printf_s("Success! Passed the FIPS 197 ECB(AES-256) KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the FIPS 197 ECB(AES-256) KAT test. \n");
	}
}

/**
* \brief Test the RHX-256 and RHX-512 implementations with KAT vectors from the CEX library
*/
void test_rhx_cex_kat()
{
	if (rhx256_ecb_kat_test() == true)
	{
		printf_s("Success! Passed the CEX++ ECB(RHX-256) KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the CEX++ ECB(RHX-256) KAT test. \n");
	}

	if (rhx512_ecb_kat_test() == true)
	{
		printf_s("Success! Passed the CEX++ ECB(RHX-512) KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the CEX++ ECB(RHX-512) KAT test. \n");
	}
}

/**
* \brief Test the RHX-256 and RHX-512 implementations CTR implementation for correct operation
*/
void test_rhx_ctr_stress()
{
	if (rhx256_ctr_stress_test() == true)
	{
		printf_s("Success! Passed the CEX++ CTR(RHX-256) stress test. \n");
	}
	else
	{
		printf_s("Failure! Failed the CEX++ CTR(RHX-256) stress test. \n");
	}

	if (rhx512_ctr_stress_test() == true)
	{
		printf_s("Success! Passed the CEX++ CTR(RHX-512) stress test. \n");
	}
	else
	{
		printf_s("Failure! Failed the CEX++ CTR(RHX-512) stress test. \n");
	}
}

/**
* \brief Test the RHX-256 and RHX-512 implementations with Monte Carlo vectors from the CEX library
*/
void test_rhx_monte_carlo()
{
	if (rhx256_monte_carlo_test() == true)
	{
		printf_s("Success! Passed the CEX++ RHX-256 Monte Carlo test. \n");
	}
	else
	{
		printf_s("Failure! Failed the CEX++ RHX-256 Monte Carlo test. \n");
	}

	if (rhx512_monte_carlo_test() == true)
	{
		printf_s("Success! Passed the CEX++ RHX-512 Monte Carlo test. \n");
	}
	else
	{
		printf_s("Failure! Failed the CEX++ RHX-512 Monte Carlo test. \n");
	}
}

/**
* \brief Test the HBA mode KAT tests
*/
void test_hba_rhx_kat()
{
	if (hba_rhx256_kat_test() == true)
	{
		printf_s("Success! Passed the RHX-256 HBA AEAD mode KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the RHX-256 HBA AEAD mode KAT test. \n");
	}

	if (hba_rhx512_kat_test() == true)
	{
		printf_s("Success! Passed the RHX-512 HBA AEAD mode KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the RHX-512 HBA AEAD mode KAT test. \n");
	}
}

/**
* \brief Run the HBA mode stress tests
*/
void test_hba_rhx_stress()
{
	if (hba_rhx256_stress_test() == true)
	{
		printf_s("Success! Passed the RHX-256 HBA AEAD mode stress test. \n");
	}
	else
	{
		printf_s("Failure! Failed the RHX-256 HBA AEAD mode stress test. \n");
	}

	if (hba_rhx512_stress_test() == true)
	{
		printf_s("Success! Passed the RHX-512 HBA AEAD mode stress test. \n");
	}
	else
	{
		printf_s("Failure! Failed the RHX-512 HBA AEAD mode stress test. \n");
	}
}

/* hkdf, hmac, and sha2 tests */

void test_sha2_kat()
{
	if (sha2_256_kat() == true)
	{
		printf_s("Success! Passed the SHA2-256 KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the SHA2-256 KAT test. \n");
	}

	if (sha2_512_kat() == true)
	{
		printf_s("Success! Passed the SHA2-512 KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the SHA2-512 KAT test. \n");
	}
}

void test_hkdf_kat()
{
	if (hkdf_256_kat() == true)
	{
		printf_s("Success! Passed the HKDF-Expand(HMAC(SHA2-256)) KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the HKDF-Expand(HMAC(SHA2-256)) KAT test. \n");
	}

	if (hkdf_512_kat() == true)
	{
		printf_s("Success! Passed the HKDF-Expand(HMAC(SHA2-512)) KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the HKDF-Expand(HMAC(SHA2-512)) test. \n");
	}
}

void test_hmac_kat()
{
	if (hmac_256_kat() == true)
	{
		printf_s("Success! Passed the HMAC(SHA2-256) KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the HMAC(SHA2-256) KAT test. \n");
	}

	if (hmac_512_kat() == true)
	{
		printf_s("Success! Passed the HMAC(SHA2-512) KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the HMAC(SHA2-512) KAT test. \n");
	}
}

/* shake, cshake, kmac, and sha3 tests */

void test_cshake_kat()
{
	if (cshake_256_kat_test() == true)
	{
		printf_s("Success! Passed the cSHAKE-256 KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the cSHAKE-256 KAT test. \n");
	}

	if (cshake_512_kat_test() == true)
	{
		printf_s("Success! Passed the cSHAKE-512 KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the cSHAKE-512 KAT test. \n");
	}
}

void test_kmac_kat()
{
	if (kmac_128_kat_test() == true)
	{
		printf_s("Success! Passed the KMAC-128 KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the KMAC-128 KAT test. \n");
	}

	if (kmac_256_kat_test() == true)
	{
		printf_s("Success! Passed the KMAC-256 KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the KMAC-256 KAT test. \n");
	}

	if (kmac_512_kat_test() == true)
	{
		printf_s("Success! Passed the KMAC-512 KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the KMAC-512 KAT test. \n");
	}
}

void test_sha3_kat()
{
	if (sha3_256_kat_test() == true)
	{
		printf_s("Success! Passed the SHA3-256 KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the SHA3-256 KAT test. \n");
	}

	if (sha3_512_kat_test() == true)
	{
		printf_s("Success! Passed the SHA3-512 KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the SHA3-512 KAT test. \n");
	}
}

void test_shake_kat()
{
	if (shake_256_kat_test() == true)
	{
		printf_s("Success! Passed the SHAKE-256 KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the SHAKE-256 KAT test. \n");
	}

	if (shake_512_kat_test() == true)
	{
		printf_s("Success! Passed the SHAKE-512 KAT test. \n");
	}
	else
	{
		printf_s("Failure! Failed the SHAKE-512 KAT test. \n");
	}
}

int main()
{
	int valid;

	valid = 1;

	if (has_aes_ni() == 1)
	{
		printf_s("AES-NI is available on this system. \n");
#if !defined(RHX_AESNI_ENABLED)
		printf_s("Add the RHX_AESNI_ENABLED flag to the preprocessor definitions to test AES-NI implementation. \n");
#else
		printf_s("The RHX_AESNI_ENABLED flag has been detected, AES-NI intrinsics are enabled. \n");
#endif
		printf_s("\n");
	}
	else
	{
		printf_s("AES-NI was not detected on this system. \n");
#if defined(RHX_AESNI_ENABLED)
		printf_s("Remove the RHX_AESNI_ENABLED flag from the preprocessor definitions to test the fallback implementation. \n");
		printf_s("Configuration settings error; AES-NI is enabled but not available on this system, check your compiler preprocessor settings. \n");
		printf_s("\n");
		valid = 0;
#endif
	}

#ifdef RHX_CSHAKE_EXTENSION
	printf_s("The CSHAKE cipher extension definition has been detected. \n");
	printf_s("Remove the RHX_CSHAKE_EXTENSION definition to enable the HKDF cipher extensions. \n");
	printf_s("\n\n");
#else
	printf_s("The HKDF cipher extension is enabled. \n");
	printf_s("Add the RHX_CSHAKE_EXTENSION definition to preprocessor flags to enable the CSHAKE cipher extensions. \n");
	printf_s("\n\n");
#endif

	if (valid == 1)
	{
		printf_s("*** Test the AES implementations using the NIST FIPS-197 AES common modes known answer tests *** \n");
		test_aes_cbc_fips();
		test_aes_ctr_fips();
		test_aes_ecb_fips();
		printf_s("\n");

		printf_s("*** Test extended cipher implementations using Stress testing, Monte Carlo, and KAT vector tests from CEX++ *** \n");
		test_rhx_cex_kat();
		test_rhx_monte_carlo();
		test_rhx_ctr_stress();
		test_hba_rhx_kat();
		test_hba_rhx_stress();
		printf_s("\n");

		printf_s("*** Test HKDF, HMAC, and SHA2 implementations using the official KAT vetors. *** \n");
		test_hkdf_kat();
		test_hmac_kat();
		test_sha2_kat();
		printf_s("\n");

		printf_s("*** Test SHAKE, cSHAKE, KMAC, and SHA3 implementations using the official KAT vetors. *** \n");
		test_shake_kat();
		test_cshake_kat();
		test_kmac_kat();
		test_sha3_kat();
		printf_s("\n");

		printf_s("Completed! Press any key to close..");
		get_response();
	}
	else
	{
		printf_s("The test has been cancelled. Press any key to close..");
		get_response();
	}

	return 0;
}

