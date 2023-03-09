/*
 * Package generator for generating UDP and TCP flows
 * Copyright (C) 2003  Martin Juhlin <juhlin@users.sourceforge.net>
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

#ifndef WMAINWIDGET_H
#define WMAINWIDGET_H

#include <umainwidget.h>

class ProcessParser;
class QListViewItem;

/**Huvudbilden
  *@author Martin Juhlin
  */

class WMainWidget : public UMainWidget
{
	Q_OBJECT
public: 
	WMainWidget(QWidget * parent = 0);
	~WMainWidget();

public slots:
	virtual void addStream();
	virtual void removeStream();
	virtual void selectedStream(QListViewItem *);

private:
	QListViewItem * m_selectedItem;
	ProcessParser * pp;
};

#endif
