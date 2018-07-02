#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("Insta");

	ofBackground(239);
	ofEnableDepthTest();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->cap.open("D:\\video\\image11.mp4");
	this->cap_size = cv::Size(160, 90);

	for (int i = 0; i < 36; i++) {

		ofImage* image = new ofImage();
		image->allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_COLOR);
		this->images.push_back(image);

		cv::Mat frame = cv::Mat(cv::Size(image->getWidth(), image->getHeight()), CV_MAKETYPE(CV_8UC3, image->getPixels().getNumChannels()), image->getPixels().getData(), 0);
		this->frames.push_back(frame);
	}

	this->number_of_frames = this->cap.get(CV_CAP_PROP_FRAME_COUNT);
	for (int i = 0; i < number_of_frames; i++) {

		cv::Mat src, mini_src;
		this->cap >> src;
		cv::resize(src, mini_src, this->cap_size);
		cv::cvtColor(mini_src, mini_src, CV_BGR2RGB);

		this->cap_frames.push_back(mini_src);
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	
	int capture_span = this->number_of_frames / 36;
	for (int i = 0; i < this->frames.size(); i++) {

		int index = (ofGetFrameNum() + i * capture_span) % this->number_of_frames;
		this->cap_frames[index].copyTo(this->frames[i]);

		this->images[i]->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int radius = 500;
	for(int i = 0; i < this->images.size(); i++){
		 
		int deg = i * 10;
		ofPoint point(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));

		ofPushMatrix();
		ofTranslate(point);
		ofRotateY(90);
		ofRotateY(45);

		this->images[i]->draw(0, 0);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}