/***
 * Maracatronics Robotics
 * Federal University of Pernambuco (UFPE) at Recife
 * http://www.maracatronics.com/
 *
 * This file is part of Armorial project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#include <QCoreApplication>
#include <src/utils/text/text.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationVersion(APP_VERSION);

    std::cout << Text::bold(Text::center(" ____                                               ")) << '\n';
    std::cout << Text::bold(Text::center("/ ___|  _   _   __ _  ___  ___  _   _  _ __    __ _ ")) << '\n';
    std::cout << Text::bold(Text::center("\\___ \\ | | | | / _` |/ __|/ __|| | | || '_ \\  / _` |")) << '\n';
    std::cout << Text::bold(Text::center(" ___) || |_| || (_| |\\__ \\\\__ \\| |_| || | | || (_| |")) << '\n';
    std::cout << Text::bold(Text::center("|____/  \\__,_| \\__,_||___/|___/ \\__,_||_| |_| \\__,_|")) << '\n';
    std::cout << Text::bold(Text::center("Made with 💛 by Maracatronics Robotics Team.")) << '\n';
    std::cout << Text::bold(Text::center("Version " + a.applicationVersion().toStdString())) << '\n' << '\n';

    bool exec = a.exec();

    return exec;
}