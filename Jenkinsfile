#!/usr/bin/env groovy

pipeline {

    environment {
        SCAN_BUILD_TMPDIR = sh(script: "mktemp -d /tmp/scan-build.XXXXXX", returnStdout: true).trim()
    }

    agent any
    stages {
        stage("Set Up") {
            steps {
                sh(script: "sudo apt-get install clang-tools",
                   label: "Downloading clang-tools for scan-build.")
            }
        }

        stage("Build and Scan") {
            steps{
                sh "scan-build -k -o ${SCAN_BUILD_TMPDIR} ./build.sh"
            }
        }
    }
    post {
        failure {
            publishHTML (target: [
                            allowMissing: false,
                            alwaysLinkToLastBuild: false,
                            keepAll: true,
                            reportDir: "${env.SCAN_BUILD_ARCHIVE}",
                            reportFiles: 'index.html',
                            reportName: "Scan-Build Report"]
            )
        }
    }
}
