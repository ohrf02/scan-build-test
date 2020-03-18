#!/usr/bin/env groovy

pipeline {

    environment {
        SCAN_BUILD_TMPDIR = sh(script: "mktemp -d /tmp/scan-build.XXXXXX", returnStdout: true).trim()
    }

    agent any
    stages {
        stage("Build and Scan") {
            steps {
                sh(script: "./build.sh ${env.SCAN_BUILD_TMPDIR}",
                   label: "Build and scan the project.")
            }
        }
    }
    post {
        failure {
            script {
                try {
                    publishHTML (target: [
                                    allowMissing: false,
                                    alwaysLinkToLastBuild: false,
                                    keepAll: true,
                                    reportDir: "${env.SCAN_BUILD_ARCHIVE}",
                                    reportFiles: 'index.html',
                                    reportName: "Scan-Build Report"])
                }
                catch(e) {
                    echo "The report doesn't exist."
                }
            }
        }
    }
}
