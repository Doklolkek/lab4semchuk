pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                git url: 'https://github.com/Doklolkek/lab4semchuk.git', credentialsId: 'github-creds'
            }
        }
        
        stage('Build') {
            steps {
                bat '"C:\\Program Files\\Microsoft Visual Studio\\2022\\Professional\\MSBuild\\Current\\Bin\\MSBuild.exe" test_repos.sln /p:Configuration=Debug /p:Platform=x64'
            }
        }

        stage('Test') {
            steps {
                bat 'x64\\Debug\\test_repos.exe --gtest_output=xml:test_report.xml'
            }
        }
    }

    post {
        always {
            junit 'test_report.xml'
        }
    }
}