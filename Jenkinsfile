#!/usr/bin/env groovy

pipeline {
    agent any
    environment {
        SCAN_BUILD_TMPDIR = sh(script: "mktemp -d /tmp/scan-build.XXXXXX", returnStdout: true).trim()
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
                    sh(script: "find code-example -type f -name '*.py' | xargs pylint --output-format=parseable > pylint.report || exit 0",
                       label: "Running pylint.")
                }
            }
        }
    }

    post {
        always {
            recordIssues enabledForFailure: true, tool: cppCheck(pattern: "cppcheck-result.xml")
            recordIssues enabledForFailure: true, tool: pyLint(pattern: "pylint.report")

            publishHTML (target: [
                            allowMissing: false,
                            alwaysLinkToLastBuild: false,
                            keepAll: true,
                            reportDir: "${env.SCAN_BUILD_TMPDIR}",
                            reportFiles: '*/**',
                            reportName: "Scan-Build Report"]
            )
        }
    }
}
