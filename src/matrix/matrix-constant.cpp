/*
 * Copyright 2010,
 * François Bleibel,
 * Olivier Stasse,
 *
 * CNRS/AIST
 *
 * This file is part of sot-core.
 * sot-core is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 * sot-core is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.  You should
 * have received a copy of the GNU Lesser General Public License along
 * with sot-core.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sot-core/matrix-constant.h>
#include <sot-core/factory.h>

using namespace std;
using namespace sot;
using namespace dynamicgraph;

DYNAMICGRAPH_FACTORY_ENTITY_PLUGIN(MatrixConstant,"MatrixConstant");

/* --------------------------------------------------------------------- */
/* --- MATRIX ---------------------------------------------------------- */
/* --------------------------------------------------------------------- */
void MatrixConstant::
commandLine( const std::string& cmdLine,
	     std::istringstream& cmdArgs, 
	     std::ostream& os )
{
  if( cmdLine == "resize" )
    {
      cmdArgs >>rows>>cols;
      ml::Matrix m(rows,cols);
      m.fill(color);
      SOUT.setConstant(m);
    }
  else if( cmdLine == "fill" )
    {
      cmdArgs >>color;
      ml::Matrix m(rows,cols);
      m.fill(color);
      SOUT.setConstant(m);
    }
  else if( cmdLine == "rand" )
    {
      ml::Matrix m(rows,cols);
      for( int i=0;i<rows;++i )
        for( int j=0;j<cols;++j )
          m(i,j) = ((rand()+0.0)/RAND_MAX*2)-1.;
      SOUT.setConstant(m);
    }
  else if( cmdLine == "ping")
    { SOUT.SignalBase<int>::setReady() ;   }
  else if( cmdLine == "eye") 
    {
      ml::Matrix m(rows,cols); m.setIdentity();
      SOUT.setConstant(m);
    }
  else if( cmdLine == "[]" ) 
    {
      unsigned int i,j; double v;
      cmdArgs >> i >> j >> v;
      ml::Matrix m = SOUT.accessCopy();
      m(i,j) = v;
      SOUT.setConstant(m);
    }
  else if( cmdLine == "help" )
    {
      os << "sotMatrixConstant"<<endl
	 << "  - resize i j\t\t:resize the output to a i x j zero matrix." <<endl
	 << "  - fill x\t\t:fill the matrix with <x> value." <<endl
	 << "  - eye\t\t:fill the matrix with 0s and a diag of 1."<<endl
	 << "  - [] i j x\t\t:set matrix[i,j] = x."<<endl;
    }
  else Entity::commandLine(cmdLine,cmdArgs,os);
}
    





