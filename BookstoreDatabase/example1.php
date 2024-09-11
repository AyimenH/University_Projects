<?php
$host = 'your_database_host';
$db   = 'your_database_name';
$user = 'your_database_user';
$pass = 'your_database_password';

// Create connection
$conn = new mysqli($host, $user, $pass, $db);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$queryId = $_GET['query'] ?? null;
$customQuery = $_POST['query'] ?? null;

$queries = [
    1 => "SELECT Book.bookName, Publisher.publisherName, Author.authorFirst, Author.authorLast
          FROM Book
          INNER JOIN Publisher ON Book.publisherID = Publisher.publisherID
          INNER JOIN Authored_By ON Book.bookID = Authored_By.bookID
          INNER JOIN Author ON Authored_By.authorID = Author.authorID;",
    2 => "SELECT Book.bookName, ROUND(SUM(Book_Order.totalAmount), 2) AS totalRevenue
          FROM Book
          INNER JOIN Book_Order ON Book.bookID = Book_Order.bookID
          GROUP BY Book.bookName;",
    3 => "SELECT authorFirst, authorLast
          FROM Author
          WHERE authorID IN (
              SELECT Authored_By.authorID 
              FROM Authored_By 
              INNER JOIN Book_Order ON Authored_By.bookID = Book_Order.bookID
              GROUP BY Authored_By.authorID 
              HAVING SUM(Book_Order.quantity) > 9
          );",
    4 => "SELECT Book.bookPrice
          FROM Book
          INNER JOIN Book_Order ON Book.bookID = Book_Order.bookID
          GROUP BY Book.bookPrice
          HAVING Book.bookPrice < 15;",
    5 => "SELECT Customer.customerFirst, Customer.customerLast, Book.bookName
          FROM Customer
          LEFT OUTER JOIN Book_Order ON Customer.customerID = Book_Order.customerID
          LEFT OUTER JOIN Book ON Book_Order.bookID = Book.bookID;"
];

$query = $queries[$queryId] ?? $customQuery;

if ($query) {
    $result = $conn->query($query);
    
    if ($result->num_rows > 0) {
        echo "<table border='1'>";
        // Fetch field names for table header
        $field_info = $result->fetch_fields();
        echo "<tr>";
        foreach ($field_info as $field) {
            echo "<th>{$field->name}</th>";
        }
        echo "</tr>";

        // Fetch rows
        while ($row = $result->fetch_assoc()) {
            echo "<tr>";
            foreach ($row as $column) {
                echo "<td>$column</td>";
            }
            echo "</tr>";
        }
        echo "</table>";
    } else {
        echo "0 results";
    }
}

$conn->close();

