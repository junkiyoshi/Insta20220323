#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	for (int z = 0; z <= 480; z += 20) {

		ofPushMatrix();
		ofTranslate(0, 0, z);

		auto deg = ofMap(ofNoise(z * 0.002 + ofGetFrameNum() * 0.01), 0, 1, -720, 720);

		this->draw_MAGATAMA(glm::vec2(), 200, deg, ofColor(0));

		ofPopMatrix();
	}

	this->cam.end();
}


//--------------------------------------------------------------
void ofApp::draw_MAGATAMA(glm::vec2 location, float radius, float rotate_deg, ofColor color) {

	float len = radius * 0.5522;
	float deg = 0;

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(rotate_deg);

	vector<glm::vec2> vertices;
	vector<pair<glm::vec2, glm::vec2>> handle_list;

	vertices.push_back(glm::vec2(0, 0));
	deg = 180;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(radius * 0.5, radius * -0.5));
	deg = 90;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(0, radius * -1));
	deg = 0;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len  * sin(deg * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(radius, 0));
	deg = 270;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * cos((deg + 180) * DEG_TO_RAD), len * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(0, radius));
	deg = 0;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(radius * -0.5, radius * 0.5));
	deg = 90;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	ofSetColor(color);
	ofFill();
	ofBeginShape();
	for (int i = 0; i < vertices.size(); i++) {

		int n = (i + 1) % vertices.size();

		ofVertex(vertices[i]);
		ofBezierVertex(handle_list[i].second, handle_list[n].first, vertices[n]);
	}

	ofNextContour(true);
	for (deg = 0; deg <= 360; deg += 5) {

		ofVertex(glm::vec2(0, radius * 0.5) + glm::vec2(radius * 0.2 * cos(deg * DEG_TO_RAD), radius * 0.2 * sin(deg * DEG_TO_RAD)));
	}
	ofEndShape(true);

	ofSetColor(ofColor(255, color.a));
	ofNoFill();
	ofBeginShape();
	for (int i = 0; i < vertices.size(); i++) {

		int n = (i + 1) % vertices.size();

		ofVertex(vertices[i]);
		ofBezierVertex(handle_list[i].second, handle_list[n].first, vertices[n]);
	}

	ofNextContour(true);
	for (deg = 0; deg <= 360; deg += 5) {

		ofVertex(glm::vec2(0, radius * 0.5) + glm::vec2(radius * 0.2 * cos(deg * DEG_TO_RAD), radius * 0.2 * sin(deg * DEG_TO_RAD)));
	}
	ofEndShape(true);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}