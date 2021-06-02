//#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

typedef long double Real;
const int nx = 32, ny = 32;
static bool hasGnuplot = NULL;
typedef Real TArra[nx + 2][ny + 2];
TArra u, v, p;

// static const string dirname = ".\\LDC_output";
static const string dirname = ".";

string args[8] = {
    // Gnuplot setup args
    "set terminal png size 1000, 1000",
    "set view map scale 1",  // Use contour
    "set autoscale yfix", "set autoscale xfix", "set xlabel 'X'",
    "set ylabel 'Y'",
    //"set pm3d interpolate 0,0", // Interpolate results with auto nr of points
    "set size ratio -1",  // Equal ticks
};

void SaveToFile(string path, TArra& arr) {
    ofstream file;

    file.open(dirname + '\\' + path);

    for (int i = 0; i <= nx; i++) {
        for (int j = 0; j <= ny; j++) {
            file << arr[i][j] << "\t";
        }
        file << endl;
    }

    file.close();
}

void RenderResults(string basename) {
    // Create pipe
    // Function name is different in Visual C++ and in GCC
#ifdef WIN32
    FILE* pipe = _popen("gnuplot", "w");
#else
    FILE* pipe = popen("gnuplot", "w");
#endif

    for (string arg : args) {  // For each loop
        fprintf(pipe, "%s\n", arg.c_str());
    }

    fprintf(pipe, "set output '%s\\%s'\n", dirname.c_str(),
            (basename + ".png").c_str());
    fprintf(pipe, "set title '%s'\n", basename.c_str());

    fprintf(pipe, "splot '%s\\%s.dat' matrix with image\n", dirname.c_str(),
            basename.c_str());
    fflush(pipe);

#ifdef WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif
}

int SaveResults(int timestamp = -1) {
    // Check if gnuplot is available
    // Run only once
    if (hasGnuplot == NULL) {
        // Check if gnuplot runs without error
        // (gnuplot -V prints version and exits)
        // > nul supresses output
        if (system("gnuplot -V > nul") == 0) {
            hasGnuplot = true;
        } else {
            hasGnuplot = false;
        }
    }

    // Create output directory
    // filesystem::create_directory(dirname);

    string ts;
    if (timestamp >= 0) {
        ts = "_" + to_string(timestamp);
    } else {
        ts = "";
    }

    SaveToFile("u" + ts + ".dat", u);
    SaveToFile("v" + ts + ".dat", v);
    SaveToFile("p" + ts + ".dat", p);

    if (hasGnuplot) {
        RenderResults("u" + ts);
        RenderResults("v" + ts);
        RenderResults("p" + ts);
    }

    return 0;
}

int main() {
    // Fill arrays with some values
    for (int i = 0; i <= nx; i++) {
        for (int j = 0; j <= ny; j++) {
            u[i][j] = rand() % 100;
            v[i][j] = rand() % 100;
            p[i][j] = rand() % 100;
        }
    }

    SaveResults();

    SaveResults(0);

    SaveResults(20);
}
