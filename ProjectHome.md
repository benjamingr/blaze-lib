![http://wiki.blaze-lib.googlecode.com/git/images/blaze300x150.jpg](http://wiki.blaze-lib.googlecode.com/git/images/blaze300x150.jpg)

**Blaze** is an open-source, high-performance C++ math library for dense and sparse arithmetic. With its state-of-the-art _Smart Expression Template_ implementation **Blaze** combines the elegance and ease of use of a domain-specific language with HPC-grade performance, making it one of the most intuitive and fastest C++ math libraries available.

The **Blaze** library offers ...

  * ... **high performance** through the integration of BLAS libraries and manually tuned HPC math kernels
  * ... **parallel execution** by OpenMP, C++11 threads and Boost threads
  * ... the **intuitive** and **easy to use** API of a domain specific language
  * ... **unified arithmetic** with dense and sparse vectors and matrices
  * ... **thoroughly tested** matrix and vector arithmetic
  * ... completely **portable**, **high quality** C++ source code

Get an impression of the clear but powerful syntax of **Blaze** in the [Getting Started](Getting_Started.md) tutorial and of the impressive performance in the [Benchmarks](Benchmarks.md) section.


---


### Download ###

<table>
<blockquote><tr>
<blockquote><td width='20px'></td>
<td><a href='https://drive.google.com/file/d/0BzMBRWLmmMSkVWNmb2hrMGVXSms/view?usp=sharing'><img src='http://wiki.blaze-lib.googlecode.com/git/images/blaze-2.3.jpg' /></a></td>
<td width='40px'></td>
<td><a href='https://drive.google.com/file/d/0BzMBRWLmmMSkY0s4RGFpbGJOLWc/view?usp=sharing'><img src='http://wiki.blaze-lib.googlecode.com/git/images/blaze-docu-2.3.jpg' /></a></td>
</blockquote></tr>
</table></blockquote>

Older releases of **Blaze** can be found in the [release archive](Release_Archive.md).


---


### News ###

**24.3.2015**: You might have heard already: Google has officially announced to shut down the Google Code platform. This is of course bad news for us since this means that we have to move the **Blaze** website and repository to a new platform. However, since there have been several requests from the **Blaze** community to move **Blaze** to a different platform we have been thinking and working in this direction for some time anyway. Given the current situation we have decided to officially move our repository with the next release of **Blaze**: Version 2.4 will be the last release on Google Code and the first release on our new home. We are currently wrapping up the 2.4 release and at the same time preparing our move to the new platform. Stay tuned, we will inform you as soon as possible about the location of our new home.

**11.3.2015**: You were asking for them, here they are! The new big feature of **Blaze** 2.3 are lower and upper triangular matrices. And they come with full support within the **Blaze** library: Specifically adapted and optimized compute kernels and full support for parallelization via OpenMP, C++11 and Boost threads. Also noteworthy: The implementation is thoroughly checked by 748 new test cases. See the **Blaze** [tutorial](Triangular_Matrices.md) for how the new LowerMatrix and UpperMatrix adaptors work!

**03.12.2014**: After a total of five and a half months, a little late for <a href='http://sc14.supercomputing.org'>SC'14</a>, but right on time for <a href='http://meetingcpp.com'>Meeting C++</a>, we finally release **Blaze** 2.2! But the waiting time was worthwhile! This release comes with several bug fixes and hundreds of improvements, many based on your hints, suggestions and ideas. Thank you very much for your support and help to make the **Blaze** library even better!

The big new feature of **Blaze** 2.2 is symmetric matrices. And this is not just any implementation of symmetric matrices, but one of the most complete and powerful implementations available. See the **Blaze** [tutorial](Symmetric_Matrices.md) to get an idea of how symmetric matrices work and how they can help you prevent some inadvertent pessimizations of your code.

**20.6.2014**: After three month, just in time for <a href='http://www.isc-events.com/isc14/'>ISC'14</a>, **Blaze** 2.1 has finally been released! The focus of this release is the improvement and extension of the shared memory parallelization capabilities. In addition to the OpenMP parallelization, **Blaze** 2.1 now also enables shared memory parallelization based on C++11 and Boost threads. With that, shared memory parallel execution is now available for virtually every platform and compiler. Additionally, the underlying architecture for the parallel execution and automatic, context-depending optimization has been significantly improved. Therefore **Blaze** 2.1 should prove to be the fastest and most flexible **Blaze** release yet.

**23.03.2014**: **Blaze** 2.0 goes parallel!

One of the main motivations of the **Blaze** 1.x releases was to provide maximum performance on a single CPU core for all possible operations. However, the <a href='http://www.gotw.ca/publications/concurrency-ddj.htm'>free lunch is over</a> and today's CPUs are not single core anymore. In order to fully utilize the performance potential of a multicore CPU, computations have to be parallelized across all available cores of a CPU. Therefore, starting with **Blaze** 2.0, the **Blaze** library provides automated shared memory parallelization. Get an impression of the possible performance boost in the [Benchmarks](Benchmarks.md) section.

Also, based on the success of **Blaze** and in order to further increase the quality of **Blaze**, we have acquired additional resources for testing purposes. For the **Blaze** 2.0 release, we have performed weeks of serial and parallel tests with 12 compilers, SSE/AVX/MIC and a total of 1764 test cases. Still, this does unfortunately not guarantee that **Blaze** is bug-free (although we of course very much hope for it). Therefore, in case you experience problems with **Blaze**, we are
extremely grateful for a bug report via

<table>
<blockquote><tr>
<blockquote><td width='300px'></td>
<td><img src='http://wiki.blaze-lib.googlecode.com/git/images/blaze-bugreport.jpg' /></td>
</blockquote></tr>
</table></blockquote>

**05.01.2014**: **Blaze** 1.5 is online! This release of the **Blaze** library is all about performance. Just like all C++ libraries using expression templates **Blaze** is heavily depending on the compiler's ability to optimize the given template code. Unfortunately several compilers, including GCC-4.7, GCC-4.8 and the Clang compiler, were not able to achieve maximum performance for many operations. In **Blaze** 1.5 we have focused on resolving the underlying problem and made it easier for the compiler to perform the necessary optimizations. Get an impression of the improved performance in the updated [Benchmarks](Benchmarks.md) section.

<a href='Hidden comment: 
*11.11.2013*: Finally, right on time for <a href="http://sc13.supercomputing.org">SC"13

Unknown end tag for &lt;/a&gt;

, we present the fifth release of the *Blaze* library. In *Blaze* 1.4 we introduce subvector and submatrix views, which in combination with rows and columns provide an amazing flexibility to access vector and matrix data. Check out this extremely versatile and powerful new feature in the [Subvectors tutorial] section.
Additionally, with *Blaze* 1.4 we have switched from the GPLv3 license to the new BSD license. From now on, *Blaze* can be freely used in any project and merely requires a copyright notice.
'></a>

<a href='Hidden comment: 
*28.07.2013*: Only two months after *Blaze* 1.2 we release the fourth version of the *Blaze* library. Version 1.3 proves to be the fastest *Blaze* release up to date due to the following new features:
* Support for AVX2 processors
* Performance optimization of several operations (including e.g. outer products)
* Complete vectorization of vector and matrix operations involving std::complex
* Serialization of vectors and matrices
'></a>

**06.06.2013**: Are you using **Blaze** in your project? Do you like it? Then we would be glad to mention your project on the **Blaze** homepage. All you have to do is send us the name, logo, and URL of your project and we will create a link on the **Blaze** main page.

<a href='Hidden comment: 
*24.05.2013*: Finally we are able to present the third release of the *Blaze* library (version 1.2). Next to a myriad of small changes and improvements, in this version we have laid the foundation for vector and matrix views. With *Blaze* 1.2 we introduce row and column views. Check out this powerful new feature in our [Rows views] tutorial.
'></a>

<a href='Hidden comment: 
*20.05.2013*: Exactly four month after the release of *Blaze* version 1.1 the next major *Blaze* release has entered the final testing phase. We are currently conducting an extensive compilation marathon on several configurations and several compilers to find the last remaining problems. However, we are confident that within the next few days we will be able to launch *Blaze* version 1.2.
'></a>

<a href='Hidden comment: 
*20.01.2013*: We are proud to present the second release of the *Blaze* library (version 1.1). Among others, *Blaze* 1.1 offers these exiting new features:
* Support for the Intel® MIC architecture
* Introduction of the 3D cross product
* Improved performance of the sparse matrix-matrix multiplication (spMMM)
* Improved support and performance for non-fundamental element types (for instance for block-structured matrices)
* Improved and extended aliasing detection and automatic optimization
* Rework of the random number generation module (for instance for the generation of random vectors and matrices)
* Improved vector and matrix output
'></a>

<a href='Hidden comment: 
*24.08.2012*: The first release of the *Blaze* library (version 1.0) is finally online! Of course we hope that everything works out of the box and that you can immediately use *Blaze* productively. However, if not, please consider that this is the very first release of *Blaze* (hopefully of many) and tell us about your problem with *Blaze*.
'></a>


---


### Wiki: Table of Contents ###
  * [Configuration and Installation](Configuration_and_Installation.md)
  * [Getting Started](Getting_Started.md)
  * Tutorial
    * Vectors
      * [Vector Types](Vector_Types.md)
      * [Vector Operations](Vector_Operations.md)
    * Matrices
      * [Matrix Types](Matrix_Types.md)
      * [Matrix Operations](Matrix_Operations.md)
    * Adaptors
      * [Symmetric Matrices](Symmetric_Matrices.md)
      * [Triangular Matrices](Triangular_Matrices.md)
    * Views
      * [Subvectors](Subvectors.md)
      * [Submatrices](Submatrices.md)
      * [Rows](Rows.md)
      * [Columns](Columns.md)
    * Arithmetic Operations
      * [Addition](Addition.md)
      * [Subtraction](Subtraction.md)
      * [Scalar Multiplication](Scalar_Multiplication.md)
      * [Vector/Vector Multiplication](Vector_Vector_Multiplication.md)
        * [Componentwise Multiplication](Vector_Vector_Multiplication#Componentwise_Multiplication.md)
        * [Inner Product / Scalar Product / Dot Product](Vector_Vector_Multiplication#Inner_Product.md)
        * [Outer Product](Vector_Vector_Multiplication#Outer_Product.md)
        * [Cross Product](Vector_Vector_Multiplication#Cross_Product.md)
      * [Matrix/Vector Multiplication](Matrix_Vector_Multiplication.md)
      * [Matrix/Matrix Multiplication](Matrix_Matrix_Multiplication.md)
    * Shared-Memory Parallelization
      * [OpenMP Parallelization](OpenMP_Parallelization.md)
      * [C++11 Thread Parallelization](Cpp_Thread_Parallelization.md)
      * [Boost Thread Parallelization](Boost_Thread_Parallelization.md)
      * [Serial Execution](Serial_Execution.md)
    * Serialization
      * [Vector Serialization](Vector_Serialization.md)
      * [Matrix Serialization](Matrix_Serialization.md)
  * [Intra-Statement Optimization](Intra_Statement_Optimization.md)
  * [Configuration Files](Configuration_Files.md)
  * [Blazemark: The Blaze Benchmark Suite](Blazemark.md)
  * [Benchmarks/Performance Results](Benchmarks.md)


---


### Bug Reports ###

We go to great lengths to guarantee a bug-free experience with the **Blaze** library. Still, unfortunately some bugs may creep in undetected. If you experience problems with **Blaze** or encounter a bug, please sent us an email with a small test program or a short error description to

<table>
<blockquote><tr>
<blockquote><td width='300px'></td>
<td><img src='http://wiki.blaze-lib.googlecode.com/git/images/blaze-bugreport.jpg' /></td>
</blockquote></tr>
</table></blockquote>

We guarantee that we will address the problem as quickly as possible and sent you feedback.


---


### License ###

The **Blaze** library is licensed under the New (Revised) BSD license. Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
  * Neither the names of the **Blaze** development group nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


---


### Compiler Compatibility ###

**Blaze** is written in C++-98 and therefore compatible with a wide range of C++ compilers. In fact, **Blaze** is constantly tested with the GNU compiler collection (version 4.5 through 4.9), the Intel C++ compiler (12.1, 13.1 and 14.0), the Clang compiler (version 3.4 through 3.6), and Visual C++ 2010, 2012 and 2013 (Win64 only). Other compilers are not explicitly tested, but might work with a high probability.


---


### Publications ###

  * K. Iglberger, G. Hager, J. Treibig, and U. Rüde: **Expression Templates Revisited: A Performance Analysis of Current Methodologies** (<a href='http://epubs.siam.org/sisc/resource/1/sjoce3/v34/i2/pC42_s1'>Download</a>). SIAM Journal on Scientific Computing, 34(2): C42--C69, 2012
  * K. Iglberger, G. Hager, J. Treibig, and U. Rüde: **High Performance Smart Expression Template Math Libraries** (<a href='http://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=06266939'>Download</a>). Proceedings of the 2nd International Workshop on New Algorithms and Programming Models for the Manycore Era (APMM 2012) at HPCS 2012


---


### Contributions ###

<table>
<blockquote><tr>
<blockquote><td width='190px'></td>
<td></td>
</blockquote></tr>
<tr>
<blockquote><td><a href='http://www.xing.com/profile/Klaus_Iglberger'>Klaus Iglberger</a></td>
<td>Project initiator and main developer</td>
</blockquote></tr>
<tr>
<blockquote><td><a href='http://www.rrze.uni-erlangen.de/wir-ueber-uns/organigramm/mitarbeiter/index.shtml/georg-hager.shtml'>Georg Hager</a></td>
<td>Performance analysis and optimization</td>
</blockquote></tr>
<tr>
<blockquote><td><a href='http://www10.informatik.uni-erlangen.de/~godenschwager/'>Christian Godenschwager</a></td>
<td>Visual Studio 2010/2012/2013 bug fixes and testing</td>
</blockquote></tr>
<tr>
<blockquote><td>Tobias Scharpff</td>
<td>Sparse matrix multiplication algorithms</td>
</blockquote></tr>
</table>