###############################
EigenApproWithGersgorin
###############################

###############################
Basic Information
###############################

**Term Project: Eigenvalue Approximation Using Gersgorin Theorem**

This project focuses on approximating eigenvalues of large matrices using the Gersgorin Circle Theorem.  
The approach includes dimensionality reduction techniques like PCA and SVD.  
The goal is to first write my own PCA and SVD methods, aiming for faster performance than existing packages.  
After implementing PCA and SVD, I plan to apply my mathematical knowledge of the Gersgorin Theorem  
to see if this approximation method can be faster. The repository contains the code and detailed explanation  
for applying this method to practical datasets.

GitHub repository: https://github.com/LienShark/EigenApproWithGersgorin

**About:**

**First Step:**  
I will begin by writing basic spectral decomposition and SVD code to use in PCA.  
I will also identify problem areas in fields such as Machine Learning (ML), Finance, or Genetic Information,  
where I can test this approach and record both the time and results of this method.

**Second Step:**  
Using the Gersgorin Theorem, I will attempt to approximate eigenvalues and perform spectral decomposition,  
with the goal of speeding up PCA compression while minimizing accuracy loss.  
Then, I will provide APIs for related applications.  
For matrices with millions of rows and columns, eigenvalue calculation can be slow and cumbersome.  
The Gersgorin Theorem states that all eigenvalues fall within certain specific circles.  
By shrinking these circles or guessing accurately within their range, I aim to avoid the tedious eigenvalue computation  
and further improve PCA efficiency.

**Final Step:**  
I will compare the two methods (traditional SVD/PCA and Gersgorin-based approach) and analyze the results.

The baseline methods will be:
1. **SVD Baseline:** Implemented using the `numpy.linalg.svd()` function from NumPy.
2. **PCA Baseline:** Using the `sklearn.decomposition.PCA()` function from Scikit-learn.


######################
Problem to Solve
######################

First, I will learn to perform SVD and spectral decomposition for PCA.  
I will also survey current methods, comparing and improving them.  
In the second phase, I hope to integrate the Gersgorin Theorem to compare results,  
aiming to trade some accuracy for increased speed.

This project has two main objectives:
1. **Speeding up PCA and SVD decomposition.**
2. **Addressing the challenge of eigenvalue computation and dimensionality reduction for large matrices.**

These challenges are common in machine learning, numerical linear algebra, and scientific computing,  
especially in areas such as NLP, genetic data analysis, and big data processing. As dataset sizes increase,  
existing tools often struggle with speed and memory limitations.

By applying the Gersgorin Theorem, I will estimate eigenvalues for large matrices and use PCA for dimensionality reduction.

### Introduction to the Gersgorin Theorem:
The Gersgorin Theorem approximates the eigenvalues of matrices.  
It states that all eigenvalues of a matrix lie within specific disks (called Gersgorin disks) on the complex plane.


######################
Prospective Users
######################

I expect this approach to shorten computation times and improve efficiency in data-intensive research,  
such as genetic data analysis and text analysis of large corpora.  
Since my approach sacrifices some accuracy for faster speed, it could be especially valuable for tasks like large-scale NLP training on personal computers.

Additionally, I will explore applications in financial modeling, machine learning, and big data processing.  
My goal is to reduce memory and computing costs during data processing, giving the project practical application value.

The baseline methods will include traditional SVD and spectral decomposition methods, which I aim to improve.


######################
System Architecture
######################

**1. Input and Output:**

- **Input:**  
  Massive matrices.  
  For larger matrices, I plan to experiment with either Incremental SVD or memory mapping to address memory limitations.  
  I will start with smaller matrices to ensure feasibility but aim to work with million-row matrices eventually.  
  If that proves impractical, I will adjust my approach accordingly.

  I will adopt the row-major approach to store my matrix because, in most cases, a row in a matrix typically represents a new data sample,
  while a column represents its features. When performing Incremental SVD, I tend to add more rows incrementally, as this approach is more meaningful in practice. 
  It also helps reduce computational complexity and simplifies storage management.
  For e.g: Today, if I need to process a matrix larger than 1000x1000, I would first load a portion of it, and then incrementally update the SVD one row at a time
  So, row-major is a relatively better choice for me.

  .. code-block:: cpp 
    class Matrix {
    public:
        Matrix(int m, int n)
        {
            m_nrow = m;
            m_ncol = n;
            m_buffer = vector<double>(m * n, 0);
        }
        
        // Row-major storage: access matrix value at (i, j)
        double& value(int i, int j)
        {
            return m_buffer[i * m_ncol + j];
        }

        // Adding a new row to the matrix (for incremental SVD)
        void addRow(const vector<double>& new_row) {
            if (new_row.size() != m_ncol) {
                throw invalid_argument("Row size does not match column size.");
            }
            m_nrow++;
            m_buffer.resize(m_nrow * m_ncol);  // Resize buffer to add the new row
            for (int j = 0; j < m_ncol; j++) {
                value(m_nrow - 1, j) = new_row[j];
            }
        }
        
        void printMatrix() const {
            for (int i = 0; i < m_nrow; i++) {
                for (int j = 0; j < m_ncol; j++) {
                    cout << m_buffer[i * m_ncol + j] << " ";
                }
                cout << endl;
            }
        }

    private:
        vector<double> m_buffer;
        int m_nrow;
        int m_ncol;
    };

- **Output:**  
  1. The low-dimensional matrix reduced by PCA and SVD (non-approximate).
  2. Approximate eigenvalues estimated using the Gersgorin Theorem, and the low-dimensional matrix reduced by PCA.

**2. System Process:**

  2.1. Read the input matrix and preprocess it.  
  2.2. Use the Gersgorin Theorem to calculate the approximate range of eigenvalues.  
  2.3. Estimate approximate eigenvalues based on the Gersgorin Theorem (solution TBD).  
  2.4. Apply PCA for dimensionality reduction.  
  2.5. Output the results to the Python API for further analysis.

**3. Module Division:**

- Eigenvalue estimation module  
- Dimensionality reduction module  
- API module



######################
API Description
######################

- **C++ API:**  
  Provides the `GersgorinEigenAppro` class to implement eigenvalue approximation,  
  and works with the `PCAReduc` class for dimensionality reduction.

- **Python API:**  
  Use `pybind11` to wrap the C++ functions and provide high-level Python interfaces,  
  such as `approximate_eigenvalue(matrix)` and `perform_pca(matrix, n_components)`.

- **Application API:**  
  If time permits, I hope to create various versions tailored for specific applications:
  - **gerNLP:** For NLP tasks.
  - **gerML:** For machine learning tasks.
  - **gerGene:** For genetic information analysis.
  - **gerFinance:** For financial modeling.


######################
Engineering Infrastructure
######################

- **Automated Build System:**  
  Use CMake to set up the C++ build system, and setuptools to build Python packages.

- **Version Control:**  
  Use Git for version management, with all development processes submitted to the GitHub repository.


######################
Timeline
######################

**Planning Phase I (2 weeks: 09/16 – 09/29):**  
  - Survey background knowledge on the following topics:  
    1. Matrix Theory (especially Gersgorin Theorem)  
    2. Eigenvalue approximation techniques  
    3. Background knowledge in NLP, ML, finance, and genetic information

**Planning Phase II (4 weeks: 09/30 – 10/20):**  
  - Write the first stage of code, including traditional PCA and SVD methods.
  - Collect test data for each field, and write a data structure for automatic testing to verify the correctness of the code.

**Week 1 (10/21):**  
  - Write preliminary architecture and simple algorithm for the second step.

**Week 2 (10/28):**  
  - Complete the implementation and test cases of the Gersgorin Theorem.
  - Test on small matrices to compare the approximate eigenvalues with actual values, and brainstorm improvements.

**Week 3 (11/04):**  
  - Complete the PCA module implementation and conduct basic testing.

**Week 4 (11/11):**  
  - Optimize memory management and attempt to process large-scale matrices, verifying if it can run successfully with extremely large inputs.

**Week 5 (11/18):**  
  - Integrate the API and complete documentation.

**Week 6 (11/25):**  
  - Develop specialized modules for applications in Finance and NLP.

**Week 7 (12/02):**  
  - Identify and correct potential problems, optimizing algorithm performance.

**Week 8 (12/09):**  
  - Write the final report and prepare for presentations.


######################
References
######################

1. Fuzhen Zhang, **Matrix Theory: Basic Results and Techniques, 2nd Edition**
