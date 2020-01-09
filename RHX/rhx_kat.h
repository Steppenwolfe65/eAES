/**
* \file rhx_kat.h
* \brief <b>AESand RHX Known Answer Tests</b> \n
* Rijndael known answer comparison (KAT) tests. \n
* The AES test vectors are from the NIST standard tests contained in AES specification document, Appendix C. \n
* FIPS 197: <a href="http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf">The Advanced Encryption Standard</a>. \n
* New vectors have been added for the extended modes RSX/RHX-256 and RSX/RHX-512, are from the CEX cryptographic library, reference: 
* The C++ <a href="https://github.com/Steppenwolfe65/CEX">CEX cryptographic library</a>
* \author John Underhill
* \date October 16, 2019
*/

#ifndef QSCTEST_RHX_KAT_H
#define QSCTEST_RHX_KAT_H

#include "common.h"

#define CTR_OUTPUT_LENGTH 33
#define MONTE_CARLO_CYCLES 10000
#define HBA_TEST_CYCLES 100

/**
* \brief Tests the CBC 128bit key KAT vectors from NIST SP800-85a.
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* SP800-38a: <a href="http://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf">Block Cipher Modes of Operations</a>
*/
bool aes128_cbc_fips_test();

/**
* \brief Tests the CBC 256-bit key KAT vectors from NIST SP800-85a.
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* SP800-38a: <a href="http://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf">Block Cipher Modes of Operations</a>
*/
bool aes256_cbc_fips_test();

/**
* \brief Tests the CTR 128bit key KAT vectors from NIST SP800-85a.
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* SP800-38a: <a href="http://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf">Block Cipher Modes of Operations</a>
*/
bool aes128_ctr_fips_test();

/**
* \brief Tests the CTR 128bit key KAT vectors from NIST SP800-85a.
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* SP800-38a: <a href="http://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf">Block Cipher Modes of Operations</a>
*/
bool aes256_ctr_fips_test();

/**
* \brief Tests the ECB mode 128bit key KAT vectors from NIST FIPS197 and SP800-85a
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* Fips197: <a href="http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf">The Advanced Encryption Standard, Appendix C.1</a>
* SP800-38a: <a href="http://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf">Block Cipher Modes of Operations</a>
*/
bool aes128_ecb_fips_test();

/**
* \brief Tests the ECB 256-bit key KAT vectors from NIST FIPS197 and SP800-85a.
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* Fips197: <a href="http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf">The Advanced Encryption Standard, Appendix C.3</a>
* SP800-38a: <a href="http://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf">Block Cipher Modes of Operations</a>
*/
bool aes256_ecb_fips_test();

/**
* \brief Tests the counter mode; CTR(RHX-256) for correct operation.
*
* \return Returns true for success
*/
bool rhx256_ctr_stress_test();

/**
* \brief Tests the counter mode; CTR(RHX-512) for correct operation.
*
* \return Returns true for success
*/
bool rhx512_ctr_stress_test();

/**
* \brief Tests the RSX/RHX 256-bit key KAT vectors from CEX.
* The C++ <a href="https://github.com/Steppenwolfe65/CEX">CEX cryptrographic library</a>
* If RHX_SHAKE_EXTENSION is defined (default) the cSHAKE extension is tested, if it is not defined, reverts to the HKDF(SHA2) extension.
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* The test uses use original (and authoritative) vectors generated by the CEX library implementation</a>
*/
bool rhx256_ecb_kat_test();

/**
* \brief Tests the RSX/RHX 512-bit key KAT vectors from CEX.
* The C++ <a href="https://github.com/Steppenwolfe65/CEX">CEX cryptrographic library</a>
* If RHX_SHAKE_EXTENSION is defined in rhx.h (default) the cSHAKE extension is tested, if it is not defined, reverts to the HKDF(SHA2) extension.
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* The test uses use original (and authoritative) vectors generated by the CEX library implementation</a>
*/
bool rhx512_ecb_kat_test();

/**
* \brief Tests the RSX/RHX 256-bit key Monte Carlo vectors from CEX.
* The C++ <a href="https://github.com/Steppenwolfe65/CEX">CEX cryptrographic library</a>
* If RHX_SHAKE_EXTENSION is defined (default) the cSHAKE extension is tested, if it is not defined, reverts to the HKDF(SHA2) extension.
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* The test uses use original (and authoritative) vectors generated by the CEX library implementation</a>
*/
bool rhx256_monte_carlo_test();

/**
* \brief Tests the RSX/RHX 512-bit key Monte Carlo vectors from CEX.
* The C++ <a href="https://github.com/Steppenwolfe65/CEX">CEX cryptrographic library</a>
* If RHX_SHAKE_EXTENSION is defined in rhx.h (default) the cSHAKE extension is tested, if it is not defined, reverts to the HKDF(SHA2) extension.
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* The test uses use original (and authoritative) vectors generated by the CEX library implementation</a>
*/
bool rhx512_monte_carlo_test();

/**
* \brief Tests the Hash Based Authentication (HBA-RSX/RHX) AEAD mode using 256-bit key KAT vectors from CEX.
* The C++ <a href="https://github.com/Steppenwolfe65/CEX">CEX cryptrographic library</a>
* If RHX_SHAKE_EXTENSION is defined in rhx.h (default) the cSHAKE extension is tested, if it is not defined, reverts to the HKDF(SHA2) extension.
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* The test uses use original (and authoritative) vectors generated by the CEX library implementation</a>
*/
bool hba_rhx256_kat_test();

/**
* \brief Tests the Hash Based Authentication (HBA-RSX/RHX) AEAD mode using 512-bit key KAT vectors from CEX.
* The C++ <a href="https://github.com/Steppenwolfe65/CEX">CEX cryptrographic library</a>
* If RHX_SHAKE_EXTENSION is defined in rhx.h (default) the cSHAKE extension is tested, if it is not defined, reverts to the HKDF(SHA2) extension.
*
* \return Returns true for success
*
* \remarks <b>Test References:</b> \n
* The test uses use original (and authoritative) vectors generated by the CEX library implementation</a>
*/
bool hba_rhx512_kat_test();

/**
* \brief Tests the HBA-RHX256 AEAD mode for correct operation.
*
* \return Returns true for success
*/
bool hba_rhx256_stress_test();

/**
* \brief Tests the HBA-RHX512 AEAD mode for correct operation.
*
* \return Returns true for success
*/
bool hba_rhx512_stress_test();

#endif
