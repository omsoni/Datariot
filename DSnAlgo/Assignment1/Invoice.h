//
//  Invoice.h
//  Assignment1
//  This file has the Invoice class with two constructors and attributes with getters and setters.
//  Created by Om Soni on 5/25/18.
//  Copyright © 2018 Om Soni. All rights reserved.
//

#include <string>
#include <stdexcept>

class Price {
public:
    explicit Price(int64_t value) :price{value} {}
    Price(){}
    int64_t getPrice() {
        return price ;
    }
    void setPrice(int64_t price) {
         price = price ;
    }
    std::string toString() {
        return "Price: " + std::to_string(price) + " with divisor" + std::to_string(divisor);
    }
private:
    const int divisor = 100;
    int64_t price ;
};

class Invoice {
public:
    Invoice(std::string partNumber, std::string partDesc, int qty, int64_t price)
    : partNumber{partNumber}, partDesc{partDesc}, price{price}, quantity{qty} {}
    Invoice() {}
    void setPartNumber(std::string partNo) {
        if (partNo.empty() | (partNo.length() != 8) )
            throw std::invalid_argument( "Invalid Part Number. Valid Parts have  8 letters" );
        partNumber = partNo ;
    }
    std::string getPartNumber() {
        return partNumber ;
    }
    void setPartDesc(std::string desc) {
        if (partDesc.empty())
            partDesc = "No part description provided.";
        partDesc = desc;
    }
    std::string getPartDesc() {
        return partDesc ;
    }
    void setPrice(int64_t price) {
        this->price.setPrice(price) ;
    }
    Price getPrice() {
        return this->price ;
    }
    void setQuantity(int qty) {
        if (qty < 0)
            qty = 0;
        if (qty > 1000000)
            throw std::invalid_argument( "Maximum allowed quantity is 10000000" );
        this->quantity = qty ;
    }
    int getQuantity() {
        return quantity;
    }
    int64_t getInvoiceAmount() {
        inv_amt = quantity * price.getPrice() ;
        return inv_amt;
    }
    
    std::string invAmttoString() {
        std::string dollars{std::to_string(getInvoiceAmount()/100)};
        std::string cents{std::to_string(getInvoiceAmount() % 100)};
        return dollars + "." + (cents.size()==1?"0":"") +cents;
    }
    std::string toString() {
        return  "PartNumber: " + partNumber + " PartDesc: "  + partDesc + " Quantity: " + std::to_string(quantity) + " Price per unit: " + price.toString()
        + " Total Invoice Amount: " + invAmttoString();
    }
private:
    std::string partNumber ;
    std::string partDesc ;
    int quantity ;
    int64_t inv_amt ;
    Price price;
};
