pipeline {
    agent any
    stages {
        stage('Checkout') {
            steps {
                git url: 'https://github.com/Doklolkek/lab4semchuk.git',
                    branch: 'main',  
                    credentialsId: 'taras'  
            }
        }
        stage('Build') {
            steps {
                bat '"path to MSBuild" test_repos.sln /t:Build /p:Configuration=Release'
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
