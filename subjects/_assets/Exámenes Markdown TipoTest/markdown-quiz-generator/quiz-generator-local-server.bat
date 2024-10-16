@echo off
python3 quiz-generator.py
cd generated-quizzes
start http://localhost:8000/
python3 -m http.server 8000
