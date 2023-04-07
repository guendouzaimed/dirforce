void progress() {
    progressCounter++;
    percent = "\r\033[1;37m" + to_string(((progressCounter * 100) / wordlistcount) / extension.size()) + "% " + to_string(progressCounter);
    cout.flush();
    cout << percent;
    cout.flush();
    cout << "\r";
}