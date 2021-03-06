/*
 * MicroHH
 * Copyright (c) 2011-2015 Chiel van Heerwaarden
 * Copyright (c) 2011-2015 Thijs Heus
 * Copyright (c) 2014-2015 Bart van Stratum
 *
 * This file is part of MicroHH
 *
 * MicroHH is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * MicroHH is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with MicroHH.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MASTER
#define MASTER

#ifdef USEMPI
#include <mpi.h>
#endif
#include <string>
#include "input.h"

class Input;

class Master
{
    public:
        Master();
        ~Master();

        void start(int, char**);
        void init(Input*);

        double get_wall_clock_time();
        bool at_wall_clock_limit();

        void wait_all();

        // overload the broadcast function
        void broadcast(char *, int);
        void broadcast(int *, int);
        void broadcast(double *, int);
        void broadcast(unsigned long *, int);

        // overload the sum function
        void sum(int *, int);
        void sum(double *, int);

        // overload the max function
        void max(double *, int);

        // overload the min function
        void min(double *, int);

        void print_message(const char *format, ...);
        void print_warning(const char *format, ...);
        void print_error  (const char *format, ...);

        std::string mode;
        std::string simname;

        int nprocs;
        int npx;
        int npy;
        int mpiid;
        int mpicoordx;
        int mpicoordy;

#ifdef USEMPI
        int nnorth;
        int nsouth;
        int neast;
        int nwest;

        MPI_Comm commxy;
        MPI_Comm commx;
        MPI_Comm commy;

        MPI_Request *reqs;
        int reqsn;
#endif

    private:
        bool initialized;
        bool allocated;

        double wall_clock_start;
        double wall_clock_end;

#ifdef USEMPI
        int check_error(int);
#endif
};
#endif
