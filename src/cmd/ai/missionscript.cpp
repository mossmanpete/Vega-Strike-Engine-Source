/* 
 * Vega Strike
 * Copyright (C) 2001-2002 Daniel Horn
 * 
 * http://vegastrike.sourceforge.net/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/*
  AI for mission scripting written by Alexander Rawass <alexannika@users.sourceforge.net>
*/

#include "script.h"
#include "navigation.h"
#include "xml_support.h"
#include "flybywire.h"
#include <stdio.h>
#include <vector>
#include <stack>
#include "vs_path.h"
#include "tactics.h"

#include "missionscript.h"
#include "cmd/script/mission.h"

AImissionScript::AImissionScript (string modname):Order (Order::MOVEMENT|Order::FACING){
  //  cout << "AImissionScript " << modname << endl;
  //printf("addr %x\n",(int)this);
  //  mission->addModule(modname);

  modulename=modname;

  classid=mission->createClassInstance(modulename);
  
  first_run=true;
}

AImissionScript::~AImissionScript () {
  //  mission->runScript(modulename,"quitai",classid);
  cout << "ai quitting" << endl;
}

void AImissionScript::Execute () {

  mission->setCurrentAIUnit(parent);
  mission->setCurrentAIOrder(this);

  if(first_run){
    mission->runScript(modulename,"initai",classid);
    first_run=false;
  }

  mission->runScript(modulename,"executeai",classid);

  if(suborders.size()!=0){
    printf("suborders: %d\n",suborders.size());
  }
  Order::Execute();
  done=false;
}
