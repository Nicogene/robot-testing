// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <rtf/TestMessage.h>
#include <rtf/TestSuit.h>
#include <rtf/Exception.h>

using namespace RTF;

TestSuit::TestSuit(std::string name)
    : RTF::Test(name),
    successful(true),
    fixtureOK(true),
    fixtureMesssage(""),
    fixtureManager(NULL),
    result(NULL),
    current(NULL) { }

TestSuit::~TestSuit() {

}

void TestSuit::addTest(RTF::Test* test) {
    tests.insert(test);
}


void TestSuit::removeTest(RTF::Test* test) {
    tests.erase(test);
}

void TestSuit::reset() {
    tests.clear();
    successful = fixtureOK =  true;
    fixtureMesssage.clear();
    fixtureManager = NULL;
    result = NULL;
}


bool TestSuit::succeeded() const {
    return successful;
}

TestResult* TestSuit::getResult() {
    return result;
}

bool TestSuit::setup() {
    bool ret = true;
    if(fixtureManager != NULL)
        ret = fixtureManager->setup();    
    return ret;
}


void TestSuit::tearDown() {
    if(fixtureManager != NULL)
        fixtureManager->tearDown();
}


void TestSuit::run(TestResult &rsl) {
    this->result = &rsl;
    successful = fixtureOK = true;
    interrupted = false;
    fixtureMesssage.clear();
    try {
        result->startTestSuit(this);
        // calling test suit setup
        if (!setup()) {
            result->addError(this, RTF::TestMessage("setup() failed!"));
            successful = false;
            result->endTestSuit(this);
            return;
        }

        // calling all test's run
        for (TestIterator it=tests.begin(); it!=tests.end(); ++it) {
            current = *it;
            // interrupted?
            if(interrupted)
                throw TestFailureException(RTF::TestMessage("interrupted!"));

            if(!fixtureOK)
                result->addError(this, fixtureMesssage);

            if(fixtureManager && !fixtureManager->check()) {
                result->addError(this, TestMessage("Fixture collapsed",
                                                   "check() failed",
                                                   RTF_SOURCEFILE(),
                                                   RTF_SOURCELINE()));
                fixtureOK = false;
            }

            // restart the fixture if it has been collapsed
            if(!fixtureOK) {
                successful = false;
                result->addReport(this, TestMessage("reports",
                                                    "restaring fixture setup",
                                                    RTF_SOURCEFILE(),
                                                    RTF_SOURCELINE()));
                tearDown();
                if(!setup())
                    throw FixtureException(RTF::TestMessage("setup() failed!"));
                if(fixtureManager && !fixtureManager->check())
                    throw FixtureException(TestMessage("Fixture collapsed",
                                                       "check() failed",
                                                       RTF_SOURCEFILE(),
                                                       RTF_SOURCELINE()));
                fixtureOK = true;
            }
            (*it)->run(*result);
            successful &= (*it)->succeeded();
        }
    }
    catch(RTF::TestFailureException& e) {
        successful = false;
        result->addFailure(this, e.message());
    }
    catch(RTF::TestErrorException& e) {
        successful = false;
        result->addError(this, e.message());
    }
    catch(RTF::FixtureException& e) {
        successful = false;
        result->addError(this, e.message());
    }
    catch(std::exception& e) {
        successful = false;
        result->addError(this, RTF::TestMessage(e.what()));
    }

    // call tearDown and catch the error exception
    try {
        tearDown();
    }
    catch(RTF::TestErrorException& e) {
        successful = false;
        result->addError(this, e.message());
    }
    catch(std::exception& e) {
        successful = false;
        result->addError(this, RTF::TestMessage(e.what()));
    }

    result->endTestSuit(this);
    current = NULL;
}


void TestSuit::setFixtureManager(RTF::FixtureManager* manager) {
    manager->setDispatcher(this);
    fixtureManager = manager;
}

RTF::FixtureManager* TestSuit::getFixtureManager() {
    return fixtureManager;
}

void TestSuit::fixtureCollapsed(RTF::TestMessage reason) {

    // we do not want to throw any exception here.
    // The reason is that if fixtureCollapsed is called
    // within other threads, the exception cannot be caught
    // by the TestSuit.
    fixtureOK = false;
    fixtureMesssage = reason;
}

void TestSuit::interrupt() {
    if(current)
        current->interrupt();
    interrupted = true;
}
