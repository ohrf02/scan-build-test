#!/usr/bin/env groovy

pipeline {
    agent any
    environment {
        SCAN_BUILD_TMPDIR = sh(script: "mktemp -d /tmp/scan-build.XXXXXX", returnStdout: true).trim()
        BUG_FOUND = false
    }

    stages {
        stage("Clang Analyzer") {
            steps {
                script{
                    sh(script: "./build.sh ${env.SCAN_BUILD_TMPDIR}",
                       label: "Build the code and scan with Clang Static Analyzer.")
                }
            }
        }

        stage("CppCheck Analyzer") {
            steps {
                script {
                    sh(script: "cppcheck --enable=all --inconclusive --xml --xml-version=2 code-example 2> cppcheck-result.xml",
                       label: "CppCheck analyzer.")
                }
            }
        }

        stage("Pylint") {
            steps{
                script {
                    sh(script: "find code-example -type f file -name '*.py' | xargs pylint -f parsable > pylint.report",
                       label: "Running pylint.")
                }
            }
        }
    }

    post {
        always {
            recordIssues enabledForFailure: true, tool: checkStyle()
            recordIssues enabledForFailure: true, tool: clangAnalyzer(pattern: "env.SCAN_BUILD_TMPDIR/*")
            recordIssues enabledForFailure: true, tool: pyLint(pattern: "pylint.report")
        }
    }
}
