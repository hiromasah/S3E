@echo off
echo .
echo GnuPG�̃C���X�g�[�����J�n���܂��B
echo ���͍��ڂ̓f�t�H���g�̂܂܂ŃC���X�g�[����i�߂Ă��������B
echo (����� ja-Japanese�܂���en-English��I�����Ă��������B)
pause
csrc\gnupg-w32cli-1.4.9.exe
echo .
echo .
echo GUI�v���O�����̃C���X�g�[�����J�n���܂��B
echo �f�X�N�g�b�v�ɃV���[�g�J�b�g���쐬���邱�Ƃ��ł��܂��B
echo �Z�L�����e�B�̌x�����\�����ꂽ�ꍇ�́A�u����͋��v��I�����Ă��������B
:LOOP
SET CHECK=
SET/P CHECK="�f�X�N�g�b�v�ɃV���[�g�J�b�g���쐬���܂���(Y/N)?:"
IF /i "%CHECK%" == "Y" GOTO LABEL1
IF /i "%CHECK%" == "N" GOTO LABEL2
GOTO LOOP
:LABEL1
makeShortCut.wsf
:LABEL2
S3E.exe -install
echo .
echo .
echo �C���X�g�[�����������܂����B
