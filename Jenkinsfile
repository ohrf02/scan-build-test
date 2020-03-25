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
                    try {
                    sh(script: "./build.sh ${env.SCAN_BUILD_TMPDIR}",
                       label: "Build the code and scan with Clang Static Analyzer.")
                    }
                    catch(e) {
                        env.BUG_FOUND = true
                        def clangAnalyzer = scanForIssues tool: clangAnalyzer(pattern: "env.SCAN_BUILD_TMPDIR/*")
                        publishIssues issues: [clangAnalyzer]

                        publishIssues id: 'analysis', name: 'All Issues',
                            issues: [clangAnalyzer],
                            filters: [includePackage('io.jenkins.plugins.analysis.*')]

                    }
                }
            }
        }

        stage("CppCheck Analyzer") {
            steps {
                script {
                    try {
                        sh(script: "cppcheck --enable=all --error-exitcode=1 --inconclusive --xml --xml-version=2 code-example 2> cppcheck-result.xml",
                           label: "Scan with CppCheck.")
                    }
                    catch(e) {
                        env.BUG_FOUND = true
                        publishCppcheck(displayAllErrors: true)
                    }
                }
            }
        }
    }

    post {
        always {
            script {
                if (env.BUG_FOUND) {
                    currentBuild.result = 'FAILURE'
                }
            }
        }
    }
}
