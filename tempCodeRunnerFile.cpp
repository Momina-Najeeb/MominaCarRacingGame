void display() const {
        if (head == NULL) {
            cout << "The list is empty." << endl;
            return;
        }

        Node* temp = head;
        int index = 1;
        while (temp != NULL) {
            cout << index << ". ";
            temp->car.display();
            temp = temp->next;
            index++;
        }
    }