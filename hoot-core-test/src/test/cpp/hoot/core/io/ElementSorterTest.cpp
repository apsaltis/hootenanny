/*
 * This file is part of Hootenanny.
 *
 * Hootenanny is free software: you can redistribute it and/or modify
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
 *
 * --------------------------------------------------------------------
 *
 * The following copyright notices are generated automatically. If you
 * have a new notice to add, please use the format:
 * " * @copyright Copyright ..."
 * This will properly maintain the copyright information. DigitalGlobe
 * copyrights will be updated automatically.
 *
 * @copyright Copyright (C) 2012, 2013, 2014 DigitalGlobe (http://www.digitalglobe.com/)
 */

// Hoot
#include <hoot/core/OsmMap.h>
#include <hoot/core/io/OsmMapReaderFactory.h>
#include <hoot/core/io/OsmMapWriterFactory.h>
#include <hoot/core/io/ElementSorter.h>

// Boost
using namespace boost;

// Qt
#include <QDebug>

#include "../TestUtils.h"

namespace hoot
{

class ElementSorterTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ElementSorterTest);
    CPPUNIT_TEST(runTest);
    CPPUNIT_TEST_SUITE_END();

public:

  void runTest()
  {
    shared_ptr<OsmMap> inputMap(new OsmMap());
    OsmMapReaderFactory::read(inputMap, "test-files/MultipolygonTest.osm", true);

    ElementSorter elementSorter(inputMap);

    int index = 0;
    while (elementSorter.hasMoreElements())
    {
      ElementPtr element = elementSorter.readNextElement();
      //LOG_DEBUG(element->toString());
      //LOG_VARD(index);
      //elements should be returned in the order nodes, ways, then relations
      if (index >= 0 && index <=15)
      {
        CPPUNIT_ASSERT(element->getElementType() == ElementType::Node);
      }
      else if (index >= 16 && index <= 19)
      {
        CPPUNIT_ASSERT(element->getElementType() == ElementType::Way);
      }
      if (index >= 20 && index <= 28)
      {
        CPPUNIT_ASSERT(element->getElementType() == ElementType::Relation);
      }
      index++;
    }
    CPPUNIT_ASSERT_EQUAL(29, index);
  }
};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(ElementSorterTest, "quick");

}



